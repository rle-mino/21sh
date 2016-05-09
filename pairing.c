/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pairing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 16:42:45 by rle-mino          #+#    #+#             */
/*   Updated: 2016/05/09 17:48:47 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tos.h"

/*
***		Parsing d'appairage
*/

static char		*pair_index(char *str)
{
	if (*str == ')' || *str == '}')
		return (str - 3);
	return (str);
}

static char		reverse_pair(char c)
{
	if (c == '{')
		return ('}');
	else if (c == '(')
		return (')');
	return (c);
}

static int		search_pair(t_line *line, char f)
{
	while (line)
	{
		if (line->c == f)
		{
			line->paired = 1;
			return (1);
		}
		line = line->next;
	}
	return (0);
}

char			*missing_pair(t_line *line)
{
	static char		prompts[5][10] = {"quote> ", "dquote> ", "subsh> ",\
										"cursh> ", "bquote"};
	static char		missing[7] = "\'\"({`";
	char			*find;
	int				paired;

	while (line)
	{
		paired = 0;
		if ((find = ft_strchr(missing, line->c)) &&
		!(paired = search_pair(line->next, reverse_pair(line->c))) &&
		line->paired == 0 && line->c)
			return (prompts[pair_index(find) - missing]);
		else if (find && paired)
			line->paired = 1;
		line = line->next;
	}
	return (NULL);
}
