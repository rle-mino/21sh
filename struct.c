/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 16:50:35 by ishafie           #+#    #+#             */
/*   Updated: 2016/05/16 23:18:57 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data			*create_data(char *content, char *prefix)
{
	t_data		*tmp;

	tmp = (t_data*)malloc(sizeof(t_data));
	if (!tmp)
	{
		ft_putstr_fd("Allocation failure, exiting..\n", 2);
		exit(EXIT_FAILURE);
	}
	tmp->content = ft_strdup(content);
	if (!(tmp->content))
		malloc_handling();
	tmp->prefix = ft_strdup(prefix);
	if (!(tmp->prefix))
		malloc_handling();
	tmp->env_var = 0;
	tmp->next = NULL;
	return (tmp);
}

int				add_back_cpy(t_env **env, char *content, char *prefix)
{
	t_data		*tmp;
	t_data		*newdata;

	newdata = NULL;
	if (!(*env))
		return (0);
	tmp = (*env)->data_backup;
	if (tmp == NULL)
	{
		(*env)->data_backup = create_data(content, prefix);
		return (1);
	}
	while (tmp->next)
		tmp = tmp->next;
	newdata = create_data(content, prefix);
	tmp->next = newdata;
	return (1);
}

int				add_back_data(t_env **env, char *content, char *prefix)
{
	t_data		*tmp;
	t_data		*newdata;

	newdata = NULL;
	if (!(*env))
		return (0);
	tmp = (*env)->data;
	if (tmp == NULL)
	{
		(*env)->data = create_data(content, prefix);
		return (1);
	}
	while (tmp->next)
		tmp = tmp->next;
	newdata = create_data(content, prefix);
	tmp->next = newdata;
	return (1);
}

t_env			*create_env(char **env)
{
	t_env		*tmp;

	tmp = (t_env*)malloc(sizeof(t_env));
	if (!tmp)
	{
		ft_putstr_fd("Allocation failure, exiting..\n", 2);
		exit(EXIT_FAILURE);
	}
	tmp->env = NULL;
	tmp->nb_env = count_env(env) + 1;
	tmp->data = NULL;
	tmp->path = NULL;
	tmp->backup = 0;
	tmp->data_backup = NULL;
	tmp->total_nb_cmd = 1;
	tmp->comd = NULL;
	tmp->nb_pipe = 0;
	tmp->ptr_first_cmd = NULL;
	tmp->tb = NULL;
	return (tmp);
}
