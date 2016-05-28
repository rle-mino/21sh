/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 00:31:10 by ishafie           #+#    #+#             */
/*   Updated: 2016/05/27 17:48:18 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			get_only_redir(char *str, int *i, int *end)
{
	while ((str)[*i] && (str)[*i] != '>' && (str)[*i] != '<')
		*i = *i + 1;
	if ((str)[*i] == 0 || (str)[*i + 1] == 0)
		return (0);
	*end = *i + 1;
	if (((str)[*end] == '>' || (str)[*end] == '<'))
	{
		*end = *end + 1;
		if ((str)[*end] == 0)
			return (0);
		if ((str)[*end] == '&')
		{
			*end = *end + 1;
			if ((str)[*end] == '-')
				*end = *end + 1;
		}
	}
	else if ((str)[*end] == '&' && (*end = *end + 1))
		if ((str)[*end] == '-')
			*end = *end + 1;
	while (*i > 0 && !ft_isspace((str)[*i]))
		*i = *i - 1;
	return (1);
}

int			choose_redir(t_env *e, char **l, int i, int *nb)
{
	(void)e;
	if (!*l || !**l || !l[i - 1])
		return (-1);
	if (ft_isdigit(l[i - 1][0]))
	{
		while (ft_isdigit(l[i - 1][*nb]))
			*nb = *nb + 1;
		if (l[i - 1][*nb] == '>' && l[i - 1][*nb + 1] == '>'
		&& l[i - 1][*nb + 2] == 0)
			return (0);
		if (l[i - 1][*nb] == '>' && l[i - 1][*nb + 1] == 0)
			return (1);
		if (ft_strcmp(&l[i - 1][*nb], ">&1") == 0)
			return (4);
	}
	else
	{
		if (l[i - 1][0] == '>' && l[i - 1][1] == '>' && l[i - 1][2] == 0)
			return (2);
		if (l[i - 1][0] == '>' && l[i - 1][1] == 0)
			return (3);
	}
	return (-1);
}

int			redirection_out_file(char **line, int i, int redir, int alt_redir)
{
	if (redir % 2 == 0 && alt_redir != 2)
		return (open(line[i], O_WRONLY | O_APPEND | O_CREAT, 0644));
	else if (alt_redir != 2)
		return (open(line[i], O_WRONLY | O_TRUNC | O_CREAT, 0644));
	return (-1);
}
