/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 00:56:10 by ishafie           #+#    #+#             */
/*   Updated: 2016/04/27 02:21:53 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tos.h"

int				init_term(void)
{
	char				area[512];
	char				*tmp;
	char				*name_term;
	struct termios		term;
	int					fd;

	fd = open(ttyname(2), O_RDWR);
	if (fd == -1)
		fd = 2;
	get_fd(fd);
	tmp = area;
	if (tcgetattr(0, &term) == -1)
		return (0);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (0);
	if ((name_term = getenv("TERM")) == NULL)
		return (0);
	if (tgetent(NULL, name_term) == ERR)
		return (0);
//	tputs(tgetstr("im", &tmp), 1, ft_putint);
//	tputs(tgetstr("mi", &tmp), 1, ft_putint);
	tputs(tgetstr("am", &tmp), 1, ft_putint);
	tputs(tgetstr("xn", &tmp), 1, ft_putint);
	return (1);
}

int				reset_term(struct termios reset)
{
	struct termios		term;
	char				area[512];
	char				*tmp;

	tmp = area;
	term = reset;
	if (tcsetattr(0, 0, &term) == -1)
		return (0);
	tputs(tgetstr("cl", &tmp), 1, ft_putint);
	return (1);
}

static void		init_fd(t_le *e)
{
	int				fd;
	char			*str;

	str = ttyname(2);
	fd = open(str, O_RDWR);
	if (fd == -1)
		fd = 2;
	e->fd = fd;
}

void			calc_col(t_le *e)
{
	struct winsize	win;
	int				fd;
	char			*str;

	str = NULL;
	str = ttyname(0);
	fd = open(str, O_RDWR);
	if (fd == -1)
		ioctl(0, TIOCGWINSZ, &win);
	else
		ioctl(fd, TIOCGWINSZ, &win);
	e->w_sizex = win.ws_col;
	e->w_sizey = win.ws_row;
}

void			init_env(t_le *e)
{
	init_fd(e);
	calc_col(e);
	get_pos_cursor(&(e->pos_x), &(e->pos_y));
}
