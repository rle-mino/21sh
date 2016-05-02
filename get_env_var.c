/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 15:22:01 by ishafie           #+#    #+#             */
/*   Updated: 2016/04/03 02:43:07 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data		*get_path(t_env *e)
{
	t_data		*tmp;

	if (!e)
		return (NULL);
	tmp = e->data;
	while (tmp)
	{
		if (ft_strcmp(tmp->prefix, "PATH") == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_data		*get_anything(t_env *e, char *choice)
{
	t_data	*tmp;

	if (!e)
		return (NULL);
	tmp = e->data;
	while (tmp)
	{
		if (ft_strcmp(tmp->prefix, choice) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_data		*get_pwd(t_env *e)
{
	t_data	*tmp;
	t_data	*home;
	int		i;

	i = 0;
	if (!e)
		return (NULL);
	home = get_anything(e, "HOME");
	tmp = get_anything(e, "PWD");
	if (!home || !tmp || !(ft_strcmp(home->content, tmp->content)))
		return (tmp);
	while (home->content[i] != '\0' && tmp->content[i] != '\0'
	&& home->content[i] == tmp->content[i])
		i++;
	if ((i == 1 && tmp->content[0] == '/') || tmp->content[i] == 0)
		i = 0;
	e->end_path = i;
	return (tmp);
}

t_data		*get_usr(t_env *e)
{
	t_data	*tmp;

	tmp = e->data;
	while (tmp)
	{
		if (ft_strcmp(tmp->prefix, "USER") == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

char		**get_args(t_env *e, char *line)
{
	char	**args;
	char	*tmp;
	int		i;

	i = 1;
	args = ft_strsplit_space(line);
	if (g_name_prog)
		free(g_name_prog);
	g_name_prog = ft_strdup(args[0]);
	while (args[i])
	{
		if (args && args[i] && args[i][0] == '~')
		{
			tmp = args[i];
			args[i] = change_to_home(e, args[i]);
			free(tmp);
		}
		i++;
	}
	return (args);
}
