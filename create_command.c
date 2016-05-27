/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 00:34:00 by ishafie           #+#    #+#             */
/*   Updated: 2016/05/27 15:51:41 by ishafie          ###   ########.fr       */
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

	if (!arg)
		return ;
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
		arg[0] = ft_strdup(str);
		arg[1] = NULL;
	}
	add_to_cmd(arg, &comd);
	e->comd = comd;
	e->ptr_first_cmd = comd;
	replace_cmd(&e);
}

void			recreate_tab(char ***str, int i, int closing)
{
	int			a;

	a = 0;
	if (!str || !*str || !**str)
		return ;
	while ((*str)[a])
		a++;
	if (closing)
		i = a + 1;
	else
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
	int			closing;

	a = 0;
	closing = 0;
	if (!e->comd || !e->comd->cmd)
		return ;
	if (i == 0)
		return (free_first_cmd(&str, i));
	while (str[a] && a < i + 2)
	{
		if (a == i)
		{
			if (!ft_strcmp(str[a], ">&-") || !ft_strcmp(str[a] + 1, ">&-") ||
			!ft_strcmp(str[a] + 1, "<&-") || !ft_strcmp(str[a], "<&-"))
				closing = 1;
			free(str[a]);
			if (!(str[a] = NULL) && !str[a + 1])
				return ;
		}
		if (closing == 0 && free_any_cmd_helper(&str, i, a) == 0)
			return ;
		a++;
	}
	recreate_tab(&str, i, closing);
}
