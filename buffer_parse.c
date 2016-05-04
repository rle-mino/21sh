/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/04 17:09:47 by rle-mino          #+#    #+#             */
/*   Updated: 2016/05/04 17:14:46 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tos.h"

void		parse_buffer(char *buffer, t_le *le)
{
	if (ft_isprint(buffer[0]))
		add_to_line(le, &(le->line), buffer[0]);
	else if (ft_is_arrow(buffer))
		move_cursor(le, ft_is_arrow(buffer), &(le->line));
	else if (ft_is_del_or_back(buffer))
		delete_char(le, &(le->line), buffer[0]);
}
