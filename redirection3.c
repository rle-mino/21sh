/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 15:55:59 by ishafie           #+#    #+#             */
/*   Updated: 2016/05/17 01:16:45 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			choose_alt_redir(t_env *e, char **line, int i)
{
	int		a;

	(void)e;
	a = 0;
	while (line[i - 1][a] != '>' && line[i - 1][a] != '<' && line[i - 1][a])
		a++;
	if (ft_strcmp(&line[i - 1][a], ">&-") == 0)
		return (2);
	else if (ft_strcmp(&line[i - 1][a], ">&") == 0)
	{
		i = i + 1;
		return (1);
	}
	return (0);
}

int			choose_alt_redir_in(char **line, int i)
{
	int		a;

	a = 0;
	while (line[i - 1][a] != '>' && line[i - 1][a] != '<' && line[i - 1][a])
		a++;
	if (ft_strcmp(&line[i - 1][a], "<<") == 0)
		return (3);
	if (ft_strcmp(&line[i - 1][a], "<&-") == 0)
		return (2);
	else if (ft_strcmp(&line[i - 1][a], "<&") == 0)
		return (1);
	return (0);
}

void		get_only_redir_helper(char *str, int *end)
{
	*end = *end + 1;
	if ((str)[*end] == '-')
		*end = *end + 1;
}

void		redirection_out_helper(char **line, int i, int alt_redir, int nb)
{
	char	*str;

	if (alt_redir == 1 || alt_redir == 2)
	{
		str = ft_strsub(line[i - 1], 0, nb);
		if (str && str[0] == 0)
			str[0] = '1';
		if (alt_redir == 2)
			close(ft_atoi(str));
		else
			dup2(ft_atoi(line[i]), ft_atoi(str));
		free(str);
	}
}

/*
***	void		redir_heredoc(t_env *e, char **line, int i)
***	{
***		char	*heredoc;
***		pid_t	father;
***		int		fd[2];
***
***		e->le.line = NULL;
***		reset_term(e->reset);
***		heredoc = edit_line_heredoc(&(e->le), line[i]);
***		pipe(fd);
***		father = fork();
***		if (father == 0)
***		{
***			close(fd[0]);
***			ft_putstr_fd(heredoc, fd[1]);
***			exit(0);
***		}
***		else
***		{
***			close(fd[1]);
***			dup2(fd[0], STDIN_FILENO);
***		}
***		init_term(e);
***		close(fd[0]);
***		close(fd[1]);
***	}
*/
