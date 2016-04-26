/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 00:56:05 by rle-mino          #+#    #+#             */
/*   Updated: 2016/04/26 03:13:16 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tos.h"

static int				init_term(struct termios **term, struct termios **reset)
{
	if (!(*term = ft_memalloc(sizeof(struct termios))))
		ft_error(MALLER);
	if (!(*reset = ft_memalloc(sizeof(struct termios))))
		ft_error(MALLER);
	if (tcgetattr(0, *term) == -1)
		return (0);
	if (tcgetattr(0, *reset) == -1)
		return (0);
	return (1);
}

static int				set_env(struct termios *term,
						struct termios *reset,
						char *term_name,
						int i)
{
	int		fd;

	if (i % 2 == 0)
	{
		if (tgetent(NULL, term_name) == ERR)
			return (0);
		term->c_lflag &= ~(ICANON);
		term->c_lflag &= ~(ECHO);
		tcsetattr(0, TCSADRAIN, term);
		fd = open(ttyname(2), O_RDWR);
		get_fd(fd);
		return (1);
	}
	else
	{
		tcsetattr(0, TCSANOW, reset);
		return (1);
	}
}

int						env_sw(void)
{
	static int				i = 0;
	static struct termios	*term;
	static struct termios	*reset;
	char					*term_name;

	term_name = getenv("TERM");
	if (!term && !(init_term(&term, &reset)))
		return (0);
	if (!(set_env(term, reset, term_name, i)))
		return (0);
	i = i ^ 1;
	return (1);
}
