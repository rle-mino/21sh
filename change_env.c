/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie  <ishafie @student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 17:20:13 by ishafie           #+#    #+#             */
/*   Updated: 2016/05/23 14:25:26 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int				check_change_env(t_env *e, char ***args, int i)
{
	int		id;
	int		flag_i;
	int		flag_u;

	flag_i = 0;
	flag_u = 0;
	id = 1;
	while ((*args)[i][id])
	{
		if ((*args)[i][id] == 'i')
			flag_i = 1;
		if ((*args)[i][id] == 'u')
			flag_u = 1;
		if ((*args)[i][id] != 'i' && (*args)[i][id] != 'u')
			return (0);
		id++;
	}
	if (flag_i)
		*args = change_env_i(&e, *args);
	else if (flag_u)
		*args = change_env_u(&e, *args);
	return (flag_i || flag_u);
}

static int				change_env_decoupage_help(char **args, int saut,
						int *save)
{
	int			i;

	i = 1;
	while (args[i] && args[i][0] == '-')
		i++;
	*save = i + saut;
	if (ft_strcmp(args[*save - 1], "-u") == 0)
		(*save) = *save + 1;
	return (i);
}

char					**change_env_decoupage(char **args, int saut)
{
	int			i;
	int			save;
	char		**new_args;
	int			id;

	save = 0;
	i = change_env_decoupage_help(args, saut, &save);
	if (args[save] == NULL)
		return (args);
	while (args[i])
		i++;
	id = 0;
	new_args = (char**)malloc(sizeof(char*) * (i + 1));
	if (!new_args)
		malloc_handling();
	while (save < i && args[save])
	{
		new_args[id] = ft_strdup(args[save]);
		save++;
		id++;
	}
	new_args[id] = NULL;
	free_args(args);
	return (new_args);
}

static int				parsing_change_env_loop(t_env *e, char ***args, int i)
{
	if ((*args)[i] && (*args)[i][0] == '-')
	{
		if (!check_change_env(e, args, i))
			return (change_env_error(*args));
	}
	else
		*args = change_env_decoupage(*args, 0);
	return (-1);
}

int						change_env(t_env *e, char ***args)
{
	if (!e || !args || !(e->data) || !(*args))
		return (0);
	if (!(*args)[1])
		return (display_env(e));
	if ((*args)[1])
		return (parsing_change_env_loop(e, args, 1));
	return (1);
}
