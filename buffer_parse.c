/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/04 17:09:47 by rle-mino          #+#    #+#             */
/*   Updated: 2016/05/09 17:45:05 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tos.h"

/*
***		Parsing du buffer
*/

void		parse_buffer(char *buffer, t_le *le)
{
	if (ft_isprint(buffer[0]))
		add_to_line(le, &(le->line), buffer[0]);
	else if (ft_is_arrow(buffer))
		move_cursor(le, ft_is_arrow(buffer), &(le->line));
	else if (ft_is_del_or_back(buffer))
		delete_char(le, &(le->line), buffer[0]);
}

void		parse_buffer_pairing(char *buffer, t_le *le)
{
	if (ft_isprint(buffer[0]))
		add_to_line(le, &(le->line), buffer[0]);
	else if (buffer[0] == 033 && buffer[1] == '[' && buffer[2] == 'D')
		move_left(le, &(le->line));
	else if (buffer[0] == 033 && buffer[1] == '[' && buffer[2] == 'C')
		move_right(le, &(le->line));
	else if (ft_is_del_or_back(buffer))
		delete_char(le, &(le->line), buffer[0]);
}
