/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/01 12:58:51 by rle-mino          #+#    #+#             */
/*   Updated: 2016/05/10 19:19:08 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tos.h"

void	move_to_first(t_le *le, t_line **line)
{
	while ((*line)->prev)
		move_left(le, line);
}

void	move_to_last(t_le *le, t_line **line)
{
	while ((*line)->next)
		move_right(le, line);
}
