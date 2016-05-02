/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tos.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 23:40:16 by rle-mino          #+#    #+#             */
/*   Updated: 2016/05/02 12:26:06 by rle-mino         ###   ########.fr       */
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

# define DEBUG fpf("%d - %s - %s\n" ,__LINE__, __func__, __FILE__);

enum
{
	LEFT = 1,
	UP,
	DOWN,
	RIGHT
};

enum
{
	GET_HOME = 1,
	GET_TERM
};

typedef struct			s_line_edit
{
	struct s_line_edit	*next;
	struct s_line_edit	*prev;
	int					x;
	int					y;
	char				c;
}						t_line;

typedef struct			s_le
{
	int					fd;
	int					fd_hist;
	int					w_sizex;
	int					w_sizey;
	int					pos_x;
	int					pos_y;
	int					res_hist;
	t_line				*line;
}						t_le;

typedef struct			s_hist
{
	t_line				*old_line;
	int					len;
	struct s_hist		*next;
	struct s_hist		*prev;
}						t_hist;

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
void					add_to_line_display(t_le *le, t_line **line);
void					delete_char_display(t_line **line);
void					redisplay_line(t_line *line);
void					get_prev_history(t_le *le);
void					get_next_history(t_le *le);
t_hist					*get_full_history(int fd);
int						linelen(t_line *line);
void					move_to_first(t_le *le, t_line **line);
char					*get_from_env(char **env, char *to_find);
t_line					*get_last(t_line *line);
t_hist					*add_hist(t_line *cmd, t_hist *prev);
void					select_old_line(int dir, t_hist **history, t_le *le);
void					*clear_hist(t_hist *hist);

#endif
