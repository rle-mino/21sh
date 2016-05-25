/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 00:38:59 by ishafie           #+#    #+#             */
/*   Updated: 2016/05/26 00:39:19 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int					go_to_home(t_env *e, char **args)
{
	t_data	*tmp;
	t_data	*pwd;
	t_data	*aux;

	if (args)
		;
	pwd = get_anything(e, "PWD");
	tmp = get_anything(e, "HOME");
	aux = get_anything(e, "OLDPWD");
	if (!tmp)
		return (0);
	if (aux && pwd)
		aux->content = pwd->content;
	if (chdir(tmp->content) == -1)
		return (cd_error(tmp->content));
	if (pwd)
		pwd->content = ft_strdup(tmp->content);
	return (0);
}

static int			get_cd_args(char **line, int i)
{
	int		id;
	int		p;

	p = 0;
	id = 1;
	while (!ft_isspace(line[i][id]) && line[i][id] != '\0')
	{
		if (line[i][id] != 'P' && line[i][id] != 'L')
			return (0);
		if (line[i][id] == 'P')
			p++;
		id++;
	}
	if (p >= 1)
		return (1);
	return (0);
}

static int			parse_args(t_env *e, char **args, char *line)
{
	int		i;
	int		p;

	p = 0;
	i = 1;
	if (!line)
		return (0);
	if (args[i] && args[i][0] == '-' && args[i + 1] == NULL && args[i][1] == 0)
		return (cd_back(e));
	while (args[i])
	{
		if (args[i][0] == '-')
			p += get_cd_args(args, i);
		if (args[i][0] != '-' || (args[i][1] != 'P' && args[i][1] != 'L'))
		{
			if (p >= 1)
				return (cd_physical(e, args, i));
			return (cd_default(e, args, i));
		}
		i++;
	}
	if (p >= 1)
		return (cd_physical(e, args, i));
	return (1);
}

void				change_directory(t_env *e, char **args, char *line)
{
	if (args && args[0] && args[1] && args[2] && args[3])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return ;
	}
	if (parse_args(e, args, line) == 1)
		cd_default(e, args, 1);
}
