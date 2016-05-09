/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 13:32:36 by ishafie           #+#    #+#             */
/*   Updated: 2016/05/09 19:22:34 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_cmd			*create_cmd(char *str)
{
	t_cmd		*newcmd;
	char		**arg;

	arg = ft_strsplit_space(str);
	newcmd = (t_cmd*)malloc(sizeof(t_cmd));
	if (!newcmd)
		malloc_handling();
	newcmd->cmd = arg;
	newcmd->next = NULL;
	return (newcmd);
}

void			add_back_cmd(t_cmd **cmd, char *arg)
{
	t_cmd		*newcmd;
	t_cmd		*tmp;

	tmp = *cmd;
	if (!tmp)
	{
		(*cmd) = create_cmd(arg);
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	newcmd = create_cmd(arg);
	tmp->next = newcmd;
}

void			create_all_cmds(t_env *e, char *str)
{
	int			i;
	char		**arg;
	t_cmd		*comd;

	comd = e->comd;
	i = 0;
	arg = NULL;
	if (e->nb_pipe > 0)
		arg = ft_strsplit(str, '|');
	else
	{
		if (!(arg = (char**)malloc(sizeof(char*) * 2)))
			malloc_handling();
			arg[0] = str;
			arg[1] = NULL;
	}
	add_to_cmd(arg, &comd);
	e->comd = comd;
	e->ptr_first_cmd = comd;
	replace_cmd(&e);
}

void			recreate_tab(char ***str, int i)
{
	int			a;

	a = 0;
	if (!str || !*str || !**str)
		return ;
	while ((*str)[a])
		a++;
	i = a + 2;
	while ((*str)[i])
	{
		(*str)[a] = (*str)[i];
		a++;
		i++;
	}
	(*str)[a] = NULL;
}

void			free_any_cmd(t_env *e, char **str, int i)
{
	int			a;

	a = 0;
	if (!e->comd || !e->comd->cmd)
		return ;
	if (i == 0)
		return (free_first_cmd(&str, i));
	while (str[a] && a < i + 2)
	{
		if (a == i)
		{
			free(str[a]);
			str[a] = NULL;
		}
		if (a == i + 1)
		{
			free(str[a]);
			str[a] = NULL;
			if (str[a + 1])
				recreate_tab(&str, i);
			return ;
		}
		a++;
	}
	recreate_tab(&str, i);
}
