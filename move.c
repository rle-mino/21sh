/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 04:20:03 by rle-mino          #+#    #+#             */
/*   Updated: 2016/04/26 04:47:41 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tos.h"

static void		move_left(t_line **line)
{
	char	buffer[1024];
	char	*buffer2;

	buffer2 = buffer;
	if ((*line)->prev)
	{
		*line = (*line)->prev;
		tputs(tgetstr("le", &buffer2), 1, ft_putint);
	}
}

static void		move_right(t_line **line)
{
	char	buffer[1024];
	char	*buffer2;

	buffer2 = buffer;
	if ((*line)->next)
	{
		*line = (*line)->next;
		tputs(tgetstr("nd", &buffer2), 1, ft_putint);
	}
}

void			move_cursor(int dir, t_line **line)
{
	if (dir == 2 || dir == 3)
		return ;
	else if (dir == 1)
		move_left(line);
	else if (dir == 4)
		move_right(line);
}
