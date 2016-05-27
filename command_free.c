/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 00:44:50 by ishafie           #+#    #+#             */
/*   Updated: 2016/05/27 16:17:42 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			closing_redir(char ***str)
{
	if (str && *str && *str + 1 && ft_strcmp((*str)[0] + 1, ">&-") == 0)
		return (1);
	if (str && *str && *str + 1 && ft_strcmp((*str)[0] + 1, "<&-") == 0)
		return (1);
	if (str && *str && *str + 1 && ft_strcmp((*str)[0] + 1, "<&") == 0)
		return (1);
	if (str && *str && *str + 1 && ft_strcmp((*str)[0] + 1, ">&") == 0)
		return (1);
	if (str && *str && *str + 1 && ft_strcmp((*str)[0], ">&-") == 0)
		return (1);
	if (str && *str && *str + 1 && ft_strcmp((*str)[0], "<&-") == 0)
		return (1);
	if (str && *str && *str + 1 && ft_strcmp((*str)[0], "<&") == 0)
		return (1);
	if (str && *str && *str + 1 && ft_strcmp((*str)[0], ">&") == 0)
		return (1);
	return (0);
}

void				free_first_cmd(char ***str, int i)
{
	int		a;
	int		closing;

	closing = closing_redir(str);
	if (!str || !*str || !(*str)[1] || (!(*str)[2] && closing != 1))
		return ;
	free((*str)[0]);
	if (closing == 0)
		free((*str)[1]);
	a = 0;
	if (closing == 1)
		i = 1;
	else
		i = 2;
	while ((*str)[i])
	{
		(*str)[a] = (*str)[i];
		a++;
		i++;
	}
	(*str)[a] = NULL;
}
