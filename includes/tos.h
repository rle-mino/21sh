/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tos.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 23:40:16 by rle-mino          #+#    #+#             */
/*   Updated: 2016/04/27 02:24:08 by ishafie          ###   ########.fr       */
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

enum
{
	LEFT = 1,
	UP,
	DOWN,
	RIGHT
};

typedef struct			s_line_edit
{
	struct s_line_edit	*next;
	struct s_line_edit	*prev;
	int					x;
	int					y;
	char				c;
}						t_line;

typedef struct			s_arg
{
	char				*content;
	int					selected;
	int					indice;
	int					len;
	int					underlined;
	struct s_arg		*prev;
	struct s_arg		*next;

}						t_arg;


typedef struct			s_le
{
	int					fd;
	int					w_sizex;
	int					w_sizey;
	int					pos_x;
	int					pos_y;
	t_line				*line;
}						t_le;

typedef struct			s_data
{
	int					env_var;
	char				*content;
	char				*prefix;
	struct s_data		*next;
}						t_data;

typedef struct			s_path
{
	char				*path;
	struct s_path		*next;
}						t_path;

typedef struct			s_env
{
	t_data				*data;
	char				**env;
	char				**path;
	int					nb_env;
	int					end_path;
	int					backup;
	t_data				*data_backup;
	t_le				le;
}						t_env;

int						env_sw(void);
char					*edit_line(t_le *le);
int						get_fd(int fd);
void					move_cursor(t_le *le, int dir, t_line **line);
int						ft_putint(int c);
t_line					*get_first(t_line *line);

int						ft_is_arrow(char *buffer);
int						ft_is_del_or_back(char *buffer);

int						init_term(void);
int						reset_term(struct termios reset);
void					init_env(t_le *e);
void					calc_col(t_le *e);

void					malloc_handling(void);
void					message_handling(void);

int						check_end_window(int winsize);
void					get_pos_cursor(int *x, int *y);

#endif
