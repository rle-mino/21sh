/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 18:16:44 by rle-mino          #+#    #+#             */
/*   Updated: 2016/05/09 18:43:29 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tos.h"

/*
***		Changement visuel de l'edition de ligne
*/

void			margin(t_le *le)
{
	int		x;
	int		x2;
	int		y;

	x = 0;
	y = 0;
	x2 = 0;
	get_pos_cursor(&x, &y);
	if (y == le->w_sizey - 1)
	{
		tputs(tgetstr("sc", NULL), 1, ft_putint);
		tputs(tgetstr("do", NULL), 1, ft_putint);
		tputs(tgetstr("rc", NULL), 1, ft_putint);
		tputs(tgetstr("up", NULL), 1, ft_putint);
	}
}

void			add_to_line_display(t_le *le, t_line **line)
{
	le->pos_x++;
	ft_putchar_fd((*line)->c, get_fd(-1));
	margin(le);
	if (le->pos_x >= le->w_sizex)
	{
		le->pos_x = 0;
		le->pos_y++;
		tputs(tgetstr("do", NULL), 1, ft_putint);
	}
	tputs(tgetstr("sc", NULL), 1, ft_putint);
	tputs(tgetstr("cd", NULL), 1, ft_putint);
	redisplay_line((*line)->next);
	tputs(tgetstr("rc", NULL), 1, ft_putint);
}

void			delete_char_display(t_line **line)
{
	tputs(tgetstr("sc", NULL), 1, ft_putint);
	tputs(tgetstr("dc", NULL), 1, ft_putint);
	tputs(tgetstr("cd", NULL), 1, ft_putint);
	redisplay_line(*line);
	tputs(tgetstr("rc", NULL), 1, ft_putint);
}

int				redisplay_line_index(t_line *line, t_le *le)
{
	t_line	*tmp;
	char	area[1024];
	int		i;
	int		x;

	i = 0;
	x = 4;
	tmp = line;
	while (tmp)
	{
		if (x == le->w_sizex)
			x = 0;
		area[i] = tmp->c;
		tmp = tmp->next;
		i++;
		x++;
	}
	area[i] = 0;
	write(get_fd(-1), area, i);
	return (x);
}

void			redisplay_line(t_line *line)
{
	t_line	*tmp;
	char	area[1024];
	int		i;

	i = 0;
	tmp = line;
	while (tmp)
	{
		area[i] = tmp->c;
		tmp = tmp->next;
		i++;
	}
	area[i] = 0;
	write(get_fd(-1), area, i);
}
