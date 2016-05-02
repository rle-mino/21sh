/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 03:18:11 by ishafie           #+#    #+#             */
/*   Updated: 2016/05/02 18:40:11 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_all_function(t_env *e, char ***args, char *line)
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

int		go_prompt(t_env *data_env, char **args)
{
	char	*path;
	int		error;

	error = 1;
	if (args && args[0] != NULL)
	{
		if ((path = check_line(args[0], data_env)) != NULL)
		{
			if (data_env && data_env->env)
				free_env_tab(data_env->env);
			actualise_env_tab(&data_env, args);
			if ((error = execve(path, args, data_env->env)) == -1)
				error_no_exec(args[0]);
		}
	}
	if (args)
		free_args(args);
	exit(0);
	return (error);
}

int		loop_prompt2(t_env *data_env, char *line)
{
	char	**args;
	pid_t	father;
	int		i;
	int		error;

	i = 0;
	error = 1;
	args = get_args(data_env, line);
	if (get_all_function(data_env, &args, line) == 0)
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

static void	before_loop_prompt2(t_env *e, int cmd, char **line, char **new_line)
{
	while (*line && cmd < e->total_nb_cmd)
	{
		if (e->total_nb_cmd > 1)
			actualise_command(line, new_line, cmd, e->total_nb_cmd);
		if (check_before_exec(*line) == 1)
			loop_prompt2(e, *line);
		if (e->total_nb_cmd <= 1)
			free(*line);
		cmd++;
	}
}

int		loop_prompt(t_env *e)
{
	char	*line;
	char	*new_line;

	line = NULL;
	new_line = NULL;
	while (42)
	{
		if (e->backup == 1)
			reverse_datacpy(&e);
		display_prompt(e);
		line = edit_line(&(e->le));
		e->total_nb_cmd = get_nb_cmd(line);
		before_loop_prompt2(e, 0, &line, &new_line);
	}
}
