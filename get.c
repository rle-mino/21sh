/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 03:12:34 by rle-mino          #+#    #+#             */
/*   Updated: 2016/05/01 22:17:25 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tos.h"

t_line		*get_last(t_line *line)
{
	while (line)
		line = line->next;
	return (line);
}

int			linelen(t_line *line)
{
	int		i;

	i = 0;
	while (line)
	{
		i++;
		line = line->next;
	}
	return (i);
}

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

void		get_pos_cursor(int *x, int *y)
{
	char	cmd[15];
	char	buf[10];

	ft_bzero(cmd, sizeof(cmd));
	ft_bzero(buf, sizeof(buf));
	ft_strcpy(cmd, "\033[6n");
	if (isatty(fileno(stdin)))
	{
		write(get_fd(-1), cmd, 5);
		read(get_fd(-1), buf, sizeof(buf));
	}
	if (ft_isdigit(buf[3]))
		*y = 10 * (buf[2] - '0') + buf[3] - '0' - 1;
	else
		*y = (buf[2] - '0') - 1;
	if (ft_isdigit(buf[6]))
		*x = 10 * (buf[5] - '0') + buf[6] - '0' - 1;
	else if (ft_isdigit(buf[5]))
		*x = (buf[5] - '0') - 1;
	else
		*x = 0;
}
