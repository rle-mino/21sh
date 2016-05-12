/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pairing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 16:42:45 by rle-mino          #+#    #+#             */
/*   Updated: 2016/05/12 19:49:35 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tos.h"

/*
***		Parsing d'appairage
*/

static int		pipe_is_alone(t_line *line)
{
	while (line)
	{
		if (line->c == '|')
		{
			while (line)
			{
				if (line->c != ' ' && line->c != '\0' && line->c != '|')
					break ;
				line = line->next;
			}
			if (!line)
				return (1);
		}
		line = line->next;
	}
	return (0);
}

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
	static char		prompts[6][10] = {"quote> ", "dquote> ", "subsh> ",\
										"cursh> ", "bquote> ", "pipe> "};
	static char		missing[7] = "\'\"({`";
	char			*find;
	int				paired;
	t_line			*first;

	first = line;
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
	if (pipe_is_alone(first))
		return (prompts[5]);
	return (NULL);
}
