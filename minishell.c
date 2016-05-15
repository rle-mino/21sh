/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 03:18:11 by ishafie           #+#    #+#             */
/*   Updated: 2016/05/15 04:37:19 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int			get_all_function(t_env *e, char ***args, char *line)
{
	if (!args || !(*args) || !((*args)[0]))
		return (0);
	if (ft_strcmp((*args)[0], "exit") == 0)
		return (my_exit(*args));
	if (ft_strcmp((*args)[0], "cd") == 0)
	{
		change_directory(e, *args, line);
		return (1);
	}
	if (ft_strcmp((*args)[0], "env") == 0)
	{
		if (change_env(e, args) == -1)
			return (0);
		return (1);
	}
	if (ft_strcmp((*args)[0], "setenv") == 0)
	{
		if (my_set_env(e, *args) == 1)
			refill_path(&e);
		return (1);
	}
	if (suite_get_all_function(e, *args) == 1)
		return (1);
	return (0);
}

int			go_prompt(t_env *data_env, char **args)
{
	int		error;

	error = 1;
	if (data_env->comd && data_env->nb_pipe > 0)
		error = recur_pipouz(data_env, data_env->comd, 0);
	else if (args && args[0] != NULL && data_env->comd)
	{
		if (redirection_cmd(data_env, data_env->comd->cmd) != -1)
		{
			error = exec_easy(data_env, data_env->comd);
		}
	}
	if (args)
		free_args(args);
	exit(0);
	return (error);
}

int			loop_prompt2(t_env *data_env, char *line)
{
	char	**args;
	pid_t	father;
	int		i;
	int		error;

	i = 0;
	error = 1;
	create_all_cmds(data_env, line);
	args = get_args(data_env, line);
	if (get_all_function(data_env, &args, line) == 0
	|| data_env->nb_pipe > 0)
	{
		father = fork();
		if (father == 0)
			error = go_prompt(data_env, args);
		else
		{
			wait(&i);
			if (i == SIGSEGV && error != -1)
				safe_exit(i);
		}
	}
	return (1);
}

/*
***	void disp_cmd(t_cmd *comd)  to delete, just testing
***	{
***		int		i;
***		t_cmd	*tmp;
***
***		tmp = comd;
***		i = 0;
***		while (tmp)
***		{
***			while (tmp->cmd[i])
***			{
***				dprintf(2, "[%s]\n", tmp->cmd[i]);
***				i++;
***			}
***			dprintf(2, "\n");
***			i = 0;
***			tmp = tmp->next;
***		}
***	}
*/

static void	before_loop_prompt2(t_env *e, int cmd, char **line, char **new_line)
{
	while (*line && cmd < e->total_nb_cmd)
	{
		if (e->ptr_first_cmd)
			free_cmd(e);
		if (e->total_nb_cmd > 1)
			actualise_command(line, new_line, cmd, e->total_nb_cmd);
		e->nb_pipe = find_pipe(*line);
		if (check_before_exec(*line) == 1)
			loop_prompt2(e, *line);
		if (e->total_nb_cmd <= 1)
			free(*line);
		cmd++;
	}
}

int			loop_prompt(t_env *e)
{
	char	*line;
	t_line	*add_to_hist;
	char	*new_line;

	line = NULL;
	new_line = NULL;
	while (42)
	{
		if (e->backup == 1)
			reverse_datacpy(&e);
		display_prompt(e);
		signal(SIGINT, restart_prompt);
		add_to_hist = edit_line(&(e->le));
		signal(SIGINT, safe_exit);
		history(FIRST_HIST, NULL);
		history(ADD_HIST, add_to_hist);
		line = to_string(add_to_hist);
		e->total_nb_cmd = get_nb_cmd(line);
		before_loop_prompt2(e, 0, &line, &new_line);
	}
}
