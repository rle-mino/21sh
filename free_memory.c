/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 00:32:57 by ishafie           #+#    #+#             */
/*   Updated: 2016/05/26 00:33:28 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			free_env_tab(char **env)
{
	free_args(env);
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
		args[i] = NULL;
		i++;
	}
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
