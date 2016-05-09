/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 20:57:04 by ishafie           #+#    #+#             */
/*   Updated: 2016/05/09 19:22:51 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int				find_redir(char **line)
{
	int			i;
	int			redir;

	i = 0;
	redir = 0;
	while (line[i])
	{
		if (line[i][0] == '>')
			redir = 1;
		if (line[i][0] == '<')
			redir = 2;
		i++;
	}
	return (redir);
}

int				get_next_redir(char **line)
{
	int			i;

	i = 0;
	while (line[i])
	{
		if (line[i][0] == '>' || line[i][0] == '<')
			return (i + 1);
		i++;
	}
	return (-1);
}

int				redirection_out(t_env *e, char **line, int i)
{
	int			out;

	if (line[i - 1][0] == '>' && line[i - 1][1] == '>')
		out = open(line[i], O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		out = open(line[i], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (out == -1)
		return (-1); // error a gerer
	dup2(out, STDOUT_FILENO);
	close(out);
	free_any_cmd(e, line, i - 1);
	return (0);
}

int				redirection_in(t_env *e, char **line, int i)
{
	int			in;

	in = open(line[i], O_RDONLY);
	if (in == -1)
		return (-1); // error a gerer;
	dup2(in, STDIN_FILENO);
	close(in);
	free_any_cmd(e, line, i - 1);
	return (0);
}

int				redirection_cmd(t_env *e, char **line)
{
	int			redir;
	int			i;
	int			error;

	error = 0;
	if (!line || !*line || (redir = find_redir(line)) == 0)
		return (0);
	if ((i = get_next_redir(line)) == -1)
		error = -1;
	if (redir == 1)
		error = redirection_out(e, line, i);
	else if (redir == 2)
		error = redirection_in(e, line, i);
	if (error != 0)
	{
		redirection_error(line, i);
		free_any_cmd(e, line, i - 1);
		return (error);
	}
	redirection_cmd(e, line);
	return (1);
}
