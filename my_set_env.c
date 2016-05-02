/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_set_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 00:34:45 by ishafie           #+#    #+#             */
/*   Updated: 2016/04/03 04:27:02 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int				already_exists_env(t_env *e, char **args)
{
	t_data		*tmp;
	t_data		*save;

	save = NULL;
	tmp = e->data;
	while (tmp)
	{
		if (ft_strcmp(tmp->prefix, args[1]) == 0)
			save = tmp;
		tmp = tmp->next;
	}
	if (save)
	{
		if (args[2])
		{
			free(save->content);
			save->content = ft_strdup(args[2]);
		}
		return (1);
	}
	return (0);
}

static int				help_unset(t_env *e, t_data *tmp, t_data *prev)
{
	if (tmp)
		e->data = tmp->next;
	if (!tmp)
		return (0);
	prev = tmp;
	free(prev);
	prev = NULL;
	return (1);
}

int						my_unset_env(t_env *e, char **args)
{
	t_data		*tmp;
	t_data		*prev;

	prev = NULL;
	if (!e || !(e->data))
		return (1);
	if (!unset_check(args))
		return (1);
	tmp = e->data;
	while (tmp)
	{
		if (ft_strcmp(tmp->prefix, args[1]) == 0)
		{
			if (prev != NULL)
				prev->next = tmp->next;
			else
				return (help_unset(e, tmp, prev));
			free(tmp);
			return (1);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}

int						my_set_env(t_env *e, char **args)
{
	if (!e || !args || !args[0])
		return (0);
	if (args[1] && args[2] && args[3])
		return (set_env_error(1));
	if (args[1] == NULL)
		return (display_env(e));
	if (!args[2])
		return (set_env_error(2));
	if (already_exists_env(e, args))
		return (1);
	e->nb_env++;
	if (args[2])
		add_back_data(&e, args[2], args[1]);
	else
		add_back_data(&e, args[2], "");
	return (1);
}
