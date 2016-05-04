/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/27 15:10:09 by ishafie           #+#    #+#             */
/*   Updated: 2016/05/04 19:00:53 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			free_env_tab(char **env)
{
	free_args(env);
	env = (char**)malloc(sizeof(char*));
	if (!env)
		malloc_handling();
	env[0] = NULL;
	env[1] = NULL;
}

void			free_args(char **args)
{
	int		i;

	i = 0;
	while (args[i] != NULL)
	{
		free(args[i]);
		i++;
	}
	free(args);
}

static void		free_data_one(t_data **lst)
{
	if ((*lst)->next == NULL)
	{
		free((*lst)->content);
		free((*lst)->prefix);
		(*lst)->content = NULL;
		(*lst)->prefix = NULL;
		free(*lst);
		(*lst) = NULL;
		return ;
	}
}

void			free_data(t_data **lst)
{
	t_data		*tmp;
	t_data		*prev;

	if (*lst == NULL)
		return ;
	free_data_one(lst);
	tmp = (*lst);
	while (tmp->next != NULL)
	{
		prev = tmp;
		tmp = tmp->next;
		free(prev->content);
		free(prev->prefix);
		prev->content = NULL;
		prev->prefix = NULL;
		free(prev);
	}
	free(tmp->content);
	free(tmp->prefix);
	free(tmp);
	(*lst) = NULL;
}

void			free_env(t_env **e)
{
	free_data(&((*e)->data));
	free_args((*e)->path);
	free(*e);
}
