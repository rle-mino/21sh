/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 02:45:11 by rle-mino          #+#    #+#             */
/*   Updated: 2016/04/27 02:59:11 by ishafie          ###   ########.fr       */
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
	char	area[1024];
	int		i;

	i = 0;
	tmp = line;
	while (tmp)
	{
		area[i] = tmp->c;
//		ft_putchar_fd(tmp->c, get_fd(-1));
		tmp = tmp->next;
		i++;
	}
	area[i] = 0;
	write(get_fd(-1), area, i);
}

int                     check_end_window(int winsize)
{
	char    cmd[15];
	char    buf[10];
	int     x;
	int		y;

	ft_bzero(cmd, sizeof(cmd));
	ft_bzero(buf, sizeof(buf));
	ft_strcpy(cmd, "\033[6n");
	if (isatty(fileno(stdin)))
	{
		write(get_fd(-1), cmd, 5);
		read(get_fd(-1), buf, sizeof(buf));
	}
	if (ft_isdigit(buf[3]))
		y = 10 * (buf[2] - '0') + buf[3] - '0';
	else
		y = (buf[2] - '0');
	if (ft_isdigit(buf[6]))
		x = 10 * (buf[5] - '0') + buf[6] - '0';
	else if (ft_isdigit(buf[5]))
		x = (buf[5] - '0');
	else
		x = 0;
	if (x >= winsize)
		ft_putchar_fd('\n', get_fd(-1));
	return (0);
}

void                    get_pos_cursor(int *x, int *y)
{
	char    cmd[15];
	char    buf[10];

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

void			add_to_line(t_le *le, t_line **line, char n, int winsize)
{
	t_line	*new;
	char	area[512];
	char	*tmp;
	int		x;
	int		y;

	/*
		cursor a la meme position que cursor 2 = ok
		cursor avant cursor 2 = not ok
	 */
	x = 0;
	y = 0;
	tmp = area;
	if (!(new = ft_memalloc(sizeof(t_line))))
		ft_error(MALLER);
//	dprintf(2, "(%d;%d)\n", le->pos_x, le->pos_y);
	new->x = le->pos_x + 1;
	new->y = le->pos_y;
	new->c = n;
	new->next = (*line)->next;
	new->prev = *line;
	if ((*line)->next)
		(*line)->next->prev = new;
	(*line)->next = new;
	*line = (*line)->next;
//	get_pos_cursor(&x, &y);
//	if (x >= winsize)
	//	ft_putchar_fd('\n', get_fd(-1));
	le->pos_x++;
	if (le->pos_x >= winsize)
	{
		le->pos_x = 0;
		le->pos_y++;
		ft_putchar_fd(92, get_fd(-1));
		ft_putchar_fd('\n', get_fd(-1));
//		tputs(tgoto(tgetstr("cm", &tmp), le->pos_x, le->pos_y), 1, ft_putint);
//		tputs(tgetstr("do", &tmp), 1, ft_putint);
	}
	ft_putchar_fd((*line)->c, get_fd(-1));
	tputs(tgetstr("sc", &tmp), 1, ft_putint);
	tputs(tgetstr("cd", &tmp), 1, ft_putint);
	redisplay_line((*line)->next);
	tputs(tgetstr("rc", &tmp), 1, ft_putint);

//	get_pos_cursor(&x, &y);
//	tputs(tgetstr("sc", &tmp), 1, ft_putint);
//	tputs(tgetstr("cd", &tmp), 1, ft_putint);
//	redisplay_line((*line)->next);
//	tputs(tgoto(tgetstr("cm", &tmp), x, y), 1, ft_putint);
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

void			delete_char(t_le *le, t_line **line, char c)
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

char			*edit_line(t_le *le)
{
	char	buffer[6];
	int		winsize;

	winsize = tgetnum("co");
	if (!(le->line = ft_memalloc(sizeof(t_line))))
		ft_error(MALLER);
	while (42)
	{
		ft_bzero(buffer, sizeof(buffer));
		read(0, buffer, 5);
		if (ft_isprint(buffer[0]))
			add_to_line(le, &(le->line), buffer[0], winsize);
		else if (ft_is_arrow(buffer))
			move_cursor(le, ft_is_arrow(buffer), &(le->line));
		else if (ft_is_del_or_back(buffer))
			delete_char(le, &(le->line), buffer[0]);
		else if (buffer[0] == '\n' && buffer[1] == 0)
		{
			le->pos_x = 0;
			break ;
		}
	}
	return (to_string(get_first((le->line))));
}
