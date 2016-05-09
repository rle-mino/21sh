/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_edit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 17:40:02 by ishafie           #+#    #+#             */
/*   Updated: 2016/05/09 19:12:42 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			add_to_cmd(char **arg, t_cmd **comd)
{
	int		i;
	char	*redir;

	redir = NULL;
	i = 0;
	while (arg && arg[i])
	{
		find_redir_str(&(arg[i]), &redir);
		add_back_cmd(comd, arg[i]);
		i++;
	}
}

char			*change_to_var(t_env *e, char *str, char *var, int i)
{
	t_data	*tmp;
	char	*final;
	char	*tmpstr;

	tmp = get_anything(e, var);
	if (!tmp)
		return (str);
	if (!str)
		return (tmp->content);
	tmpstr = ft_strsub(str, 0, i);
	final = ft_strjoin(tmpstr, tmp->content);
	free(tmpstr);
	return (final);
}

void			check_and_replace(t_env *e, char **str)
{
	int			i;
	char		*tmp;

	i = 0;
	if ((*str)[0] == '~')
	{
		tmp = (*str);
		*str = change_to_home(e, (*str));
		free(tmp);
	}
	while ((*str)[i])
	{
		if ((*str)[i] == '$')
		{
			tmp = (*str);
			*str = change_to_var(e, (*str), *str + 1 + i, i);
			free(tmp);
		}
		i++;
	}
}

void			replace_cmd(t_env **e)
{
	t_cmd		*comd;
	int			i;

	i = 0;
	if (!e || !*e)
		return ;
	comd = (*e)->comd;
	if (!comd)
		return ;
	while (comd)
	{
		while (comd->cmd[i])
		{
			check_and_replace(*e, &(comd->cmd[i]));
			i++;
		}
		i = 0;
		comd = comd->next;
	}
}
