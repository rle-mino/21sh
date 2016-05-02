/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 18:16:44 by rle-mino          #+#    #+#             */
/*   Updated: 2016/05/01 11:05:08 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tos.h"

void			add_to_line_display(t_le *le, t_line **line)
{
	char	area[512];
	char	*tmp;
	int		x;
	int		y;

	x = 0;
	y = 0;
	tmp = area;
	le->pos_x++;
	ft_putchar_fd((*line)->c, get_fd(-1));
	if (le->pos_x >= le->w_sizex)
	{
		le->pos_x = 0;
		le->pos_y++;
		tputs(tgetstr("do", &tmp), 1, ft_putint);
	}
	tputs(tgetstr("sc", &tmp), 1, ft_putint);
	tputs(tgetstr("cd", &tmp), 1, ft_putint);
	redisplay_line((*line)->next);
	tputs(tgetstr("rc", &tmp), 1, ft_putint);
}

void			delete_char_display(t_line **line)
{
	char	area[512];
	char	*tmp;

	tmp = area;
	tputs(tgetstr("sc", &tmp), 1, ft_putint);
	tputs(tgetstr("dc", &tmp), 1, ft_putint);
	tputs(tgetstr("cd", &tmp), 1, ft_putint);
	redisplay_line(*line);
	tputs(tgetstr("rc", &tmp), 1, ft_putint);
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
