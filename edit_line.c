/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 02:45:11 by rle-mino          #+#    #+#             */
/*   Updated: 2016/04/26 08:25:32 by ishafie          ###   ########.fr       */
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
void			redisplay_line(t_line *line)
{
	t_line	*tmp;

	tmp = line;
	while (tmp)
	{
		ft_putchar_fd(tmp->c, get_fd(-1));
		tmp = tmp->next;
	}
}

void			get_cursor_to_end(t_line **line)
{
	t_line	*tmp;
	char	area[512];
	char	*tmpd;

	tmpd = area;
	tmp = *line;
	while (tmp)
	{
		tputs(tgetstr("nd", &tmpd), 1, ft_putint);
		tmp = tmp->next;
	}
}

void			add_to_line(t_line **line, char n)
{
	t_line	*new;
	char	area[512];
	char	*tmp;

	tmp = area;
	if (!(new = ft_memalloc(sizeof(t_line))))
		ft_error(MALLER);
	new->c = n;
	new->next = (*line)->next;
	new->prev = *line;
	if ((*line)->next)
		(*line)->next->prev = new;
	(*line)->next = new;
	*line = (*line)->next;
//	tputs(tgetstr("sc", &tmp), 1, ft_putint);
//	get_cursor_to_end(line);
//	tputs(tgetstr("nd", &tmp), 1, ft_putint);
//	move_cursor(RIGHT, line);
//	tputs(tgetstr("le", &tmp), 1, ft_putint);
//	tputs(tgetstr("rc", &tmp), 1, ft_putint);
	ft_putchar_fd((*line)->c, get_fd(-1));
//	tputs(tgetstr("sc", &tmp), 1, ft_putint);
//	tputs(tgetstr("cd", &tmp), 1, ft_putint);
//	redisplay_line((*line)->next);
//	tputs(tgetstr("rc", &tmp), 1, ft_putint);
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

void			delete_char(t_line **line, char c)
{
	t_line		*tmp;

	tmp = *line;
	if (!*line)
		return ;
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	if (tmp && tmp->next == NULL && c != 127)
		move_cursor(LEFT, line);
	if (tmp)
		free(tmp);
 	tmp = NULL;
	if (c == 127)
		move_cursor(LEFT, line);
	else if (*line && (*line)->next)
		*line = (*line)->next;
	delete_char_display(&((*line)->next));
}

char			*edit_line(t_le *le)
{
	char	buffer[6];

	if (!(le->line = ft_memalloc(sizeof(t_line))))
		ft_error(MALLER);
	while (42)
	{
		ft_bzero(buffer, sizeof(buffer));
		read(0, buffer, 5);
		if (ft_isprint(buffer[0]))
			add_to_line(&(le->line), buffer[0]);
		else if (ft_is_arrow(buffer))
			move_cursor(ft_is_arrow(buffer), &(le->line));
		else if (ft_is_del_or_back(buffer))
			delete_char(&(le->line), buffer[0]);
		else if (buffer[0] == '\n' && buffer[1] == 0)
			break ;
	}
	return (to_string(get_first((le->line))));
}
