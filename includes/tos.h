/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tos.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 23:40:16 by rle-mino          #+#    #+#             */
/*   Updated: 2016/05/04 18:52:43 by rle-mino         ###   ########.fr       */
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

# define DEBUG fpf("%d - %s - %s\n" ,__LINE__, __func__, __FILE__)

enum
{
	LEFT = 1,
	UP,
	DOWN,
	RIGHT
};

enum
{
	READ_HIST,
	WRITE_HIST,
	NEXT_HIST,
	PREV_HIST,
	FIRST_HIST,
	ADD_HIST,
	RUP_HIST
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
	int					w_sizex;
	int					w_sizey;
	int					pos_x;
	int					pos_y;
	t_line				*line;
}						t_le;

typedef struct			s_hist
{
	t_line				*old_line;
	int					len;
	struct s_hist		*next;
	struct s_hist		*prev;
}						t_hist;

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
	int					total_nb_cmd;
}						t_env;

int						env_sw(void);
int						get_fd(int fd);
t_env					*get_t_env(t_env *env);
char					*get_from_env(char **env, char *to_find);
int						init_term(t_env *e);
int						reset_term(struct termios reset);
void					init_env(t_le *e, t_env *env);
void					calc_col(t_le *e);
void					malloc_handling(void);
void					message_handling(void);
int						check_end_window(int winsize);
/*
***
***		LINE EDIT
***
*/
char					*edit_line(t_le *le);
int						ft_is_arrow(char *buffer);
int						ft_is_del_or_back(char *buffer);
void					get_pos_cursor(int *x, int *y);
void					add_to_line_display(t_le *le, t_line **line);
void					delete_char_display(t_line **line);
void					redisplay_line(t_line *line);
int						linelen(t_line *line);
void					move_to_first(t_le *le, t_line **line);
t_line					*get_last(t_line *line);
void					margin(t_le *le);
void					move_left(t_le *le, t_line **line);
char					*to_string(t_line *line);
int						ft_putint(int c);
void					move_cursor(t_le *le, int dir, t_line **line);
t_line					*get_first(t_line *line);
void					add_to_line(t_le *le, t_line **line, char n);
void					delete_char(t_le *le, t_line **line, char c);
void					parse_buffer(char *buffer, t_le *le);
/*
***		history
*/
t_line					*history(int query, t_line *line);
t_hist					*read_history(t_env *env);
void					write_history(t_hist *hist, t_env *env);
void					*clear_hist(t_hist *hist);
t_hist					*add_hist(t_line *cmd, t_hist *next, t_hist *prev);
t_line					*to_line(char *cmd);

#endif
