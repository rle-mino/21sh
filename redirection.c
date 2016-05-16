/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 20:57:04 by ishafie           #+#    #+#             */
/*   Updated: 2016/05/16 23:30:04 by ishafie          ###   ########.fr       */
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
		if (line[i][0] == '>' || line[i][1] == '>')
		{
			redir = 1;
			return (1);
		}
		if (line[i][0] == '<' || line[i][1] == '<')
		{
			redir = 2;
			return (2);
		}
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
		if (line[i][1] == '>' || line[i][1] == '<')
			return (i + 1);
		if (line[i][0] == '>' || line[i][0] == '<')
			return (i + 1);
		i++;
	}
	return (-1);
}

int				redirection_out(t_env *e, char **line, int i)
{
	int			out;
	int			redir;
	int			alt_redir;
	int			nb;

	nb = 0;
	out = -1;
	alt_redir = choose_alt_redir(e, line, i);
	redir = choose_redir(e, line, i, &nb);
	if (redir % 2 == 0 && alt_redir != 2)
		out = open(line[i], O_WRONLY | O_APPEND | O_CREAT, 0644);
	else if (alt_redir != 2)
		out = open(line[i], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (out == -1 && alt_redir == 0)
		return (-1);
	redirection_out_helper(line, i, alt_redir, nb);
	if (alt_redir != 1 && alt_redir != 2 &&
	out != -1 && (redir == 1 || redir == 0))
		dup2(out, ft_atoi(ft_strsub(line[i - 1], 0, nb)));
	else if (out != -1)
		dup2(out, STDOUT_FILENO);
	if (out != -1 && alt_redir != 2)
		close(out);
	free_any_cmd(e, line, i - 1);
	return (0);
}

int				redirection_in(t_env *e, char **line, int i)
{
	int			in;
	int			alt_redir;
	int			redir;
	int			nb;

	redir = choose_redir(e, line, i, &nb);
	alt_redir = choose_alt_redir_in(line, i);
	if (alt_redir == 1 || alt_redir == 2)
	{
		if (alt_redir == 2)
			close(ft_atoi(ft_strsub(line[i - 1], 0, nb)));
		else
			dup2(STDIN_FILENO, ft_atoi(ft_strsub(line[i - 1], 0, nb)));
	}
	else if (alt_redir == 3)
	{
		char buf[10];
		ft_bzero(buf, sizeof(buf));
		fflush(STDIN_FILENO);
		getchar();
		read(0, buf, 9);
		redir_heredoc(e, line, i);
	}
	else
	{
		in = open(line[i], O_RDONLY);
		if (in == -1 && alt_redir == 0)
			return (-1);
		dup2(in, STDIN_FILENO);
		close(in);
	}
	free_any_cmd(e, line, i - 1);
	return (0);
}

int				redirection_cmd(t_env *e, char **line)
{
	int			redir;
	int			i;
	int			error;

	error = 0;
/*	int a = 0;
	while (line[a])
	dprintf(2, "line = %s\n", line[a++]);*/
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
