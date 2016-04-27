/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 04:20:03 by rle-mino          #+#    #+#             */
/*   Updated: 2016/04/27 02:36:31 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tos.h"

static void		move_left(t_le *le, t_line **line)
{
	char	buffer[1024];
	char	*buffer2;

	buffer2 = buffer;
	if ((*line)->prev)
	{
		*line = (*line)->prev;
		le->pos_x--;
//		tputs(tgoto(tgetstr("cm", &buffer2), (*line)->x, (*line)->y), 1, ft_putint);
		tputs(tgetstr("le", &buffer2), 1, ft_putint);
	}
}

static void		move_right(t_le *le, t_line **line)
{
	char	buffer[1024];
	char	*buffer2;

	buffer2 = buffer;
	if ((*line)->next)
	{
		le->pos_x++;
		*line = (*line)->next;
//		tputs(tgoto(tgetstr("cm", &buffer2), (*line)->x, (*line)->y), 1, ft_putint);
		tputs(tgetstr("nd", &buffer2), 1, ft_putint);
	}
}

void			move_cursor(t_le *le, int dir, t_line **line)
{
	if (dir == 2 || dir == 3)
		return ;
	else if (dir == 1)
		move_left(le, line);
	else if (dir == 4)
		move_right(le, line);
}
