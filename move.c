/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 04:20:03 by rle-mino          #+#    #+#             */
/*   Updated: 2016/05/05 22:18:54 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tos.h"

void			move_left(t_le *le, t_line **line)
{
	char	buffer[1024];
	char	*buffer2;

	buffer2 = buffer;
	if ((*line)->prev)
	{
		*line = (*line)->prev;
		if (le->pos_x == 0)
		{
			tputs(tgetstr("up", &buffer2), 1, ft_putint);
			while (le->pos_x++ < le->w_sizex)
				tputs(tgetstr("nd", &buffer2), 1, ft_putint);
			le->pos_x--;
		}
		else
		{
			le->pos_x--;
			tputs(tgetstr("le", &buffer2), 1, ft_putint);
		}
	}
}

static void		move_right(t_le *le, t_line **line)
{
	char	buffer[1024];
	char	*buffer2;

	buffer2 = buffer;
	if ((*line)->next)
	{
		if (le->pos_x == (le->w_sizex) && !(le->pos_x = 0))
			tputs(tgetstr("do", &buffer2), 1, ft_putint);
		else
		{
			tputs(tgetstr("nd", &buffer2), 1, ft_putint);
			le->pos_x++;
		}
		*line = (*line)->next;
	}
}

void			move_cursor(t_le *le, int dir, t_line **line)
{
	void	*o;
	t_line	*tmp;

	o = NULL;
	if (dir == 2 || dir == 3)
	{
		move_to_first(le, line);
		tputs(tgetstr("cd", NULL), 1, ft_putint);
		tmp = get_first_line(le->line);
		le->line = dir == 2 ? history(PREV_HIST, *line) : history(NEXT_HIST, o);
		if (!tmp->is_orig)
			clear_line(tmp);
		redisplay_line(le->line);
		le->pos_x = linelen(le->line);
		*line = get_last_line(le->line);
	}
	else if (dir == 1)
		move_left(le, line);
	else if (dir == 4)
		move_right(le, line);
}
