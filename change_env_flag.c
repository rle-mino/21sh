/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env_flag.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 23:05:32 by ishafie           #+#    #+#             */
/*   Updated: 2016/05/16 17:41:20 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int						reverse_datacpy(t_env **e)
{
	t_data		*tmp;

	if (!e || !*e)
		return (0);
	if ((*e)->data)
		free_data(&((*e)->data));
	(*e)->backup = 0;
	tmp = (*e)->data_backup;
	while (tmp)
	{
		add_back_data(e, tmp->content, tmp->prefix);
		tmp = tmp->next;
	}
	return (0);
}

static int				datacpy(t_env **e)
{
	t_data		*tmp;

	if (!e || !*e)
		return (0);
	tmp = (*e)->data;
	while (tmp)
	{
		add_back_cpy(e, tmp->content, tmp->prefix);
		tmp = tmp->next;
	}
	return (0);
}

char					**change_env_i(t_env **e, char **args)
{
	if (e && *e)
		(*e)->backup = 1;
	if ((*e)->data_backup)
		free_data(&((*e)->data_backup));
	datacpy(e);
	free_data(&((*e)->data));
	(*e)->env[0] = NULL;
	args = change_env_decoupage(args, 0);
	return (args);
}

static char				**change_env_error_arg(t_env **e, char **args)
{
	display_env(*e);
	return (args);
}

char					**change_env_u(t_env **e, char **args)
{
	int			i;

	i = 1;
	while (args[i] && args[i][0] == '-')
		i++;
	if (i < 3)
		return (args);
	if (!args[i + 1])
		return (change_env_error_arg(e, args));
	if (e && *e)
		(*e)->backup = 1;
	if ((*e)->data_backup)
		free_data(&((*e)->data_backup));
	datacpy(e);
	if (args[i])
		my_unset_env(*e, args + (i - 1));
	args = change_env_decoupage(args, 1);
	return (args);
}
