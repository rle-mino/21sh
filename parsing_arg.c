/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 15:18:59 by ishafie           #+#    #+#             */
/*   Updated: 2016/04/27 04:20:07 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (line[0] == '.' && line[1] == '/')
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
