/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 04:20:03 by rle-mino          #+#    #+#             */
/*   Updated: 2016/05/04 18:57:01 by rle-mino         ###   ########.fr       */
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

t_line			*history(int query, t_line *line)
{
	static t_hist		*history = NULL;

	if (query == RUP_HIST)
		history->old_line = line;
	else if (query == READ_HIST)
		history = read_history(get_t_env(NULL));
	else if (query == NEXT_HIST && history->next)
		history = history->next;
	else if (query == PREV_HIST && history->prev)
		history = history->prev;
	else if (query == WRITE_HIST)
		write_history(history, get_t_env(NULL));
	else if (query == FIRST_HIST)
		while (history->next)
			history = history->next;
	else if (query == ADD_HIST)
	{
		history->next = add_hist(line, NULL, history);
		history = history->next;
	}
	return (history->old_line);
}

void			move_cursor(t_le *le, int dir, t_line **line)
{
	void	*o;

	o = NULL;
	if (dir == 2 || dir == 3)
	{
		move_to_first(le, line);
		tputs(tgetstr("cd", NULL), 1, ft_putint);
		le->line = dir == 2 ? history(PREV_HIST, *line) : history(NEXT_HIST, o);
		redisplay_line(le->line);
		le->pos_x = linelen(le->line);
		*line = get_last(le->line);
	}
	else if (dir == 1)
		move_left(le, line);
	else if (dir == 4)
		move_right(le, line);
}
