/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 14:21:43 by rle-mino          #+#    #+#             */
/*   Updated: 2016/05/24 21:52:28 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tos.h"

t_line		*cpy_line(t_line *line)
{
	t_line	*cpy;
	t_line	*tmp;

	cpy = ft_memalloc(sizeof(t_line));
	line = line->next;
	tmp = cpy;
	while (line)
	{
		tmp->next = ft_memalloc(sizeof(t_line));
		tmp->next->c = line->c;
		tmp->next->prev = tmp;
		tmp = tmp->next;
		line = line->next;
	}
	return (cpy);
}

void		clear_line(t_line *line)
{
	line = line->next;
	while (line && line->next)
	{
		free(line->prev);
		line = line->next;
	}
	free(line);
}
