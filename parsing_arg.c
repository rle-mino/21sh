/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 15:18:59 by ishafie           #+#    #+#             */
/*   Updated: 2016/05/27 17:22:24 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char			*exec_line(char *line)
{
	if (access(line, F_OK) == 0)
		return (error_handler(line));
	return (error_not_found(line));
}

static char			*access_without_path(char *line)
{
	if (access(line, F_OK) != 0)
		return (error_not_found(line));
	return (line);
}

char				*check_line(char *line, t_env *e)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!e || !(e->path))
		return (access_without_path(line));
	if (line && *line &&
	((line[0] == '.' && line[1] == '/') || (line[0] == '/')))
		return (exec_line(line));
	while (e->path[i])
	{
		tmp = ft_strjoin_slash(e->path[i], line);
		if (!tmp)
			malloc_handling();
		if (access(tmp, F_OK) == 0)
			return (error_handler(tmp));
		free(tmp);
		i++;
	}
	return (error_not_found(line));
}

int					exec_easy(t_env *e, t_cmd *comd)
{
	char			*path;
	int				error;

	error = 1;
	if (!e || !e->comd || !e->comd->cmd)
		return (-1);
	if ((path = check_line(comd->cmd[0], e)) != NULL)
	{
		if (e && e->env)
			free_env_tab(e->env);
		actualise_env_tab(&e, comd->cmd);
		if ((error = execve(path, comd->cmd, e->env)) == -1)
			error_no_exec(comd->cmd[0]);
	}
	return (error);
}
