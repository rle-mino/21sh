/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 02:45:11 by rle-mino          #+#    #+#             */
/*   Updated: 2016/04/26 04:55:34 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tos.h"

char			*to_string(t_line *line)
{
	char	buffer[2];
	char	*string;
	char	*tmp;

	if (!(string = ft_memalloc(1)))
		ft_error(MALLER);
	while (line)
	{
		ft_bzero(buffer, sizeof(buffer));
		buffer[0] = line->c;
		tmp = string;
		string = ft_strjoin(string, buffer);
		free(tmp);
		line = line->next;
	}
	return (string);
}

void			add_to_line(t_line **line, char n)
{
	t_line	*new;

	if ((*line)->c == 0)
		(*line)->c = n;
	else
	{
		if (!(new = ft_memalloc(sizeof(t_line))))
			ft_error(MALLER);
		new->c = n;
		new->next = (*line)->next;
		new->prev = *line;
		if ((*line)->next)
			(*line)->next->prev = new;
		(*line)->next = new;
		*line = (*line)->next;
	}
	ft_putchar_fd((*line)->c, get_fd(-1));
}

char			*edit_line(void)
{
	char	buffer[6];
	t_line	*line;

	if (!(line = ft_memalloc(sizeof(t_line))))
		ft_error(MALLER);
	while (42)
	{
		ft_bzero(buffer, sizeof(buffer));
		read(0, buffer, 5);
		if (ft_isprint(buffer[0]))
			add_to_line(&line, buffer[0]);
		else if (ft_is_arrow(buffer))
			move_cursor(ft_is_arrow(buffer), &line);
		else if (buffer[0] == '\n' && buffer[1] == 0)
			break ;
	}
	return (to_string(get_first(line)));
}
