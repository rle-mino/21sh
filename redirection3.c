/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 15:55:59 by ishafie           #+#    #+#             */
/*   Updated: 2016/05/15 04:29:40 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			choose_alt_redir(t_env *e, char **line, int i)
{
	int		a;

	(void)e;
	a = 0;
	while (line[i - 1][a] != '>' && line[i - 1][a] != '<' && line[i - 1][a])
		a++;
	if (ft_strcmp(&line[i - 1][a], ">&-") == 0)
		return (2);
	else if (ft_strcmp(&line[i - 1][a], ">&") == 0)
	{
		i = i + 1;
		return (1);
	}
	return (0);
}

int			choose_alt_redir_in(char **line, int i)
{
	int		a;

	a = 0;
	while (line[i - 1][a] != '>' && line[i - 1][a] != '<' && line[i - 1][a])
		a++;
	if (ft_strcmp(&line[i - 1][a], "<&-") == 0)
		return (2);
	else if (ft_strcmp(&line[i - 1][a], "<&") == 0)
		return (1);
	return (0);
}

void		get_only_redir_helper(char *str, int *end)
{
	*end = *end + 1;
	if ((str)[*end] == '-')
		*end = *end + 1;
}

void		redirection_out_helper(char **line, int i, int alt_redir, int nb)
{
	char	*str;

	if (alt_redir == 1 || alt_redir == 2)
	{
		str = ft_strsub(line[i - 1], 0, nb);
		if (alt_redir == 2)
			close(ft_atoi(str));
		else
			dup2(ft_atoi(line[i]), ft_atoi(str));
		free(str);
	}
}
