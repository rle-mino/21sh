/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tos.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 23:40:16 by rle-mino          #+#    #+#             */
/*   Updated: 2016/04/26 04:45:42 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOS_H
# define TOS_H

# include "libft.h"
# include "colors.h"
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <fcntl.h>

typedef struct			s_line_edit
{
	struct s_line_edit	*next;
	struct s_line_edit	*prev;
	char				c;
}						t_line;

int						env_sw(void);
char					*edit_line(void);
int						get_fd(int fd);
int						ft_is_arrow(char *buffer);
void					move_cursor(int dir, t_line **line);
int						ft_putint(int c);
t_line					*get_first(t_line *line);

#endif
