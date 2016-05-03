/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 00:56:10 by ishafie           #+#    #+#             */
/*   Updated: 2016/05/03 18:06:47 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tos.h"
#include "minishell.h"

int				init_term(t_env *e)
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
	if (get_anything(e, "TERM") == NULL)
		return (0);
	name_term = get_anything(e, "TERM")->content;
	if (tgetent(NULL, name_term) == ERR)
		return (0);
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

void			init_env(t_le *e, t_env *env)
{
	char	*hist_path;
	t_data	*tmp;

	init_fd(e);
	calc_col(e);
	if (!(tmp = get_anything(env, "HOME")))
		hist_path = "";
	else
		hist_path = ft_strjoin(tmp->content, "/.history");
	get_pos_cursor(&(e->pos_x), &(e->pos_y));
	if ((e->fd_hist = open(hist_path, O_RDWR | O_APPEND)) == -1)
		ft_putstr_fd("history unavailable\n", 2);
}
