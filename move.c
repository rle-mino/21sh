/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 04:20:03 by rle-mino          #+#    #+#             */
/*   Updated: 2016/05/03 14:02:46 by rle-mino         ###   ########.fr       */
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

void			get_history(t_le *le, int dir)
{
	static t_hist		*history = NULL;

	if (le->res_hist == 1)
	{
		history = clear_hist(history);
		le->res_hist = 0;
	}
	if (history)
	{
		history->next = add_hist(le->line, history);
		history = history->next;
	}
	else
		history = add_hist(le->line, NULL);
	select_old_line(dir, &history, le);
}

void			move_cursor(t_le *le, int dir, t_line **line)
{
	if (dir == 2 || dir == 3)
	{
		//move_to_first(le, line);
		//tputs(tgetstr("cd", NULL), 1, ft_putint);
		//get_history(le, dir);
		//redisplay_line(le->line);
	}
	else if (dir == 1)
		move_left(le, line);
	else if (dir == 4)
		move_right(le, line);
}
