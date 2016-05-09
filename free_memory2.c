/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 17:20:12 by ishafie           #+#    #+#             */
/*   Updated: 2016/05/07 20:01:16 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void		free_tab(char **str)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (str[len])
		len++;
	while (i < len)
	{
		free(str[i]);
		i++;
	}
}

void		free_cmd(t_env *e)
{
	t_cmd	*tmp;
	t_cmd	*prev;

	if (!e || !e->comd)
		return ;
	tmp = e->comd;
	prev = NULL;
	if (!tmp->next)
	{
		free(e->comd);
		e->comd = NULL;
		return ;
	}
	while (tmp)
	{
		prev = tmp;
		tmp = tmp->next;
		free_tab(prev->cmd);
		prev->cmd = NULL;
		free(prev);
		prev = NULL;
	}
	free(tmp);
	e->comd = NULL;
}
