/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 16:21:58 by ishafie           #+#    #+#             */
/*   Updated: 2016/05/09 19:20:51 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_redir_str(char **str, int i, char **redir)
{
	char	*prefix;
	char	*tmp;

	prefix = ft_strsub(*str, 0, i);
	tmp = *redir;
	*redir = ft_strjoin(prefix, *redir);
	free(tmp);
	if ((*str)[i + 1] == '>' || (*str)[i + 1] == '<')
		tmp = ft_strjoin(*redir, *str + i + 2);
	else
		tmp = ft_strjoin(*redir, *str + i + 1);
	free(*str);
	free(*redir);
	*str = tmp;
}

int			find_redir_str(char **str, char **redir)
{
	int		i;

	i = 0;
	while ((*str)[i] != '>' && (*str)[i] != '>' && (*str)[i])
		i++;
	if (((*str)[i] != '>' && (*str)[i] != '<') || (*str)[i] == 0)
		return (0);
	if ((*str)[i + 1] == 0 || (((*str)[i + 1] == '>' || (*str)[i + 1] == '<') &&
		(*str)[i + 2] == 0))
		return (0);
	if ((*str)[i] == '>' && (*str)[i + 1] == '>')
		*redir = ft_strdup(">> ");
	else if ((*str)[i] == '<' && (*str)[i + 1] == '<')
		*redir = ft_strdup("<< ");
	else if ((*str)[i] == '>')
		*redir = ft_strdup("> ");
	else if ((*str)[i] == '<')
		*redir = ft_strdup("< ");
	else
		return (0);
	change_redir_str(str, i, redir);
	return (1);
}
