/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 02:45:11 by rle-mino          #+#    #+#             */
/*   Updated: 2016/05/04 19:10:30 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tos.h"

char				*to_string(t_line *line)
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

void			add_to_line(t_le *le, t_line **line, char n)
{
	t_line	*new;

	new = ft_memalloc(sizeof(t_line));
	new->x = le->pos_x + 1;
	new->y = le->pos_y;
	new->c = n;
	new->next = (*line)->next;
	new->prev = *line;
	if ((*line)->next)
		(*line)->next->prev = new;
	(*line)->next = new;
	*line = (*line)->next;
	add_to_line_display(le, line);
}

void			delete_char(t_le *le, t_line **line, char c)
{
	t_line		*tmp;

	tmp = *line;
	if (!*line || !(*line)->prev)
		return ;
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	if (tmp && tmp->next == NULL && c != 127)
		move_cursor(le, LEFT, line);
	if (tmp)
		free(tmp);
	tmp = NULL;
	if (c == 127)
		move_cursor(le, LEFT, line);
	else if (*line && (*line)->next)
		*line = (*line)->next;
	delete_char_display(&((*line)->next));
}

char				*edit_line(t_le *le)
{
	char	buffer[6];

	le->pos_x = 4;
	if (!(le->line = ft_memalloc(sizeof(t_line))))
		ft_error(MALLER);
	history(RUP_HIST, le->line);
	while (42)
	{
		margin(le);
		ft_bzero(buffer, sizeof(buffer));
		read(0, buffer, 5);
		parse_buffer(buffer, le);
		if (buffer[0] == '\n' && buffer[1] == 0)
		{
			le->pos_x = 0;
			tputs(tgetstr("do", NULL), 1, ft_putint);
			break ;
		}
	}
	return (to_string(get_first(le->line)));
}
