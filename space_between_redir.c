/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_between_redir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 18:59:26 by rle-mino          #+#    #+#             */
/*   Updated: 2016/05/15 20:05:00 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tos.h"

void		insert_space_in_line(t_line **line)
{
	t_line	*new;

	new = ft_memalloc(sizeof(t_line));
	new->c = ' ';
	new->next = (*line)->next;
	new->prev = *line;
	if ((*line)->next)
		(*line)->next->prev = new;
	(*line)->next = new;
	(*line) = (*line)->next;
}

t_line		*add_space_between_redir(t_line *line)
{
	t_line		*first;

	first = line;
	while (line)
	{
		if (line->c == '>' && line->next && line->next->c != '&'
				&& line->next->c != '-' && !ft_isspace(line->next->c)
				&& !ft_isdigit(line->next->c) && line->next->c != '>')
			insert_space_in_line(&line);
		else if (line && line->c == '>')
		{
			line = line->next;
			while (line && (line->c == '&' || line->c == '-' || line->c == '>'))
				line = line->next;
			if (line && line->c != ' ')
				line = line->prev;
			insert_space_in_line(&line);
		}
		if (line)
			line = line->next;
	}
	return (first);
}
