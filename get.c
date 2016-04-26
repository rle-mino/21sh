/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 03:12:34 by rle-mino          #+#    #+#             */
/*   Updated: 2016/04/26 04:50:54 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tos.h"

t_line		*get_first(t_line *line)
{
	while (line->prev)
		line = line->prev;
	return (line);
}

int			get_fd(int fd)
{
	static int	o_fd = -1;

	if (o_fd == -1)
		o_fd = fd;
	return (o_fd);
}
