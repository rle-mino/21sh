/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 13:30:26 by ishafie           #+#    #+#             */
/*   Updated: 2016/05/08 22:25:40 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int					find_pipe(char *str)
{
	int				i;
	int				nb_pipe;

	nb_pipe = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
			nb_pipe++;
		i++;
	}
	return (nb_pipe);
}

static int			error_pipe(int a)
{
	if (a == 1)
		ft_putstr_fd("42sh: couldn't create pipe\n", 2);
	else if (a == 2)
		ft_putstr_fd("42sh: couldn't dup2\n", 2);
	return (-1);
}

static void			fils_cmd(t_env *e, int pipefd[2], t_cmd *comd)
{
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	redirection_cmd(e, comd->cmd);
	exec_easy(e, comd);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
}

int					recur_pipouz(t_env *e, t_cmd *comd, int i)
{
	pid_t			pid;
	int				pipefd[2];

	if (comd->next == NULL)
	{
		redirection_cmd(e, comd->cmd);
		return (exec_easy(e, comd));
	}
	if (!comd)
		return (0);
	if (pipe(pipefd) == -1)
		return (error_pipe(1));
	if ((pid = fork()) == 0)
		fils_cmd(e, pipefd, comd);
	else
	{
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
			return (error_pipe(2));
		close(pipefd[1]);
		return (recur_pipouz(e, comd->next, i));
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid, NULL, 0);
	return (0);
}
