/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 17:20:12 by ishafie           #+#    #+#             */
/*   Updated: 2016/05/15 04:18:45 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int			free_any_cmd_helper(char ***str, int i, int a)
{
	if (a == i + 1)
	{
		free((*str)[a]);
		(*str)[a] = NULL;
		if ((*str)[a + 1])
			recreate_tab(str, i);
		return (0);
	}
	return (1);
}

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

void		free_arbre(t_arbre *a)
{
	if (!(*a))
		return ;
	if (a == NULL)
		return ;
	(*a)->lettre = 0;
	if ((*a)->filsg)
		free_arbre(&(*a)->filsg);
	if ((*a)->frered)
		free_arbre(&(*a)->frered);
	free(*a);
	(*a) = NULL;
}
