/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/01 12:58:51 by rle-mino          #+#    #+#             */
/*   Updated: 2016/05/01 22:35:43 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tos.h"

void	move_to_first(t_le *le, t_line **line)
{
	while ((*line)->prev)
	{
		if (le->pos_x == 0)
		{
			tputs(tgetstr("up", NULL), 1, ft_putint);
			while (le->pos_x++ < le->w_sizex)
				tputs(tgetstr("nd", NULL), 1, ft_putint);
			le->pos_x--;
		}
		else
		{
			tputs(tgetstr("le", NULL), 1, ft_putint);
			le->pos_x--;
		}
		*line = (*line)->prev;
	}
}
