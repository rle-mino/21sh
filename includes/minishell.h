/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 17:13:03 by ishafie           #+#    #+#             */
/*   Updated: 2016/05/27 20:12:39 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "tos.h"
# include "arbre.h"
# include <dirent.h>
# include <fcntl.h>
# include <time.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# define YELLOW "\e[1;33m"
# define BLUE "\e[0;36m"
# define RED "\e[0;31m"
# define WHITE "\e[1;37m"
# define PURPLE "\e[1;35m"
# define STOP "\e[0m"
# define CYAN "\e[1;36m"
# define GREEN "\e[1;32m"

char					*g_name_prog;

int						exec_easy(t_env *e, t_cmd *comd);

void					free_cmd(t_env *e);
void					free_tab(char **str);

/*
***		REDIRECTION
*/
int						redirection_cmd(t_env *e, char **line);
int						redirection_error(char **line, int i);
int						choose_redir(t_env *e, char **l, int i, int *nb);

int						str_redir_ok(char **str);
int						find_redir(char **line);
int						choose_alt_redir(t_env *e, char **line, int i);
int						choose_alt_redir_in(char **line, int i);
void					redir_heredoc(void);

void					get_only_redir_helper(char *str, int *end);
void					redirection_out_helper(char **line, int i,
						int alt_redir, int nb);
int						redirection_out_file(char **line, int i, int redir,
						int alt_redir);

/*
***		STRUCT COMMAND
*/
t_cmd					*create_cmd(char *str);
void					create_all_cmds(t_env *e, char *str);
void					add_back_cmd(t_cmd **cmd, char *arg);
void					free_any_cmd(t_env *e, char **str, int i);
void					recreate_tab(char ***str, int i, int closing);

int						free_any_cmd_helper(char ***str, int i, int a);

void					replace_cmd(t_env **e);

void					free_first_cmd(char ***str, int i);
void					add_to_cmd(char **arg, t_cmd **comd);

/*
***		MULTI COMMAND
*/
int						get_nb_cmd(char *line);
void					actualise_command(char **line, char **new_line,
						int cmd, int n_cmd);

/*
***		PIPE
*/
int						find_pipe(char *str);
int						recur_pipouz(t_env *e, t_cmd *comd, int i);

void					safe_exit(int a);

int						fill_env(t_env **e, char **env);
int						fill_path(t_env **e, char *path);
int						count_env(char **env);

char					*check_line(char *line, t_env *e);

int						check_before_exec(char *line);

t_data					*get_path(t_env *e);
char					**get_args(t_env *e, char *line);
t_data					*get_pwd(t_env *e);
t_data					*get_usr(t_env *e);
t_data					*get_anything(t_env *e, char *choice);

int						my_exit(char **args);

int						my_set_env(t_env *e, char **args);
int						my_unset_env(t_env *e, char **args);

int						set_env_error(int a);
int						unset_check(char **args);

void					actualise_anything(t_env *e, char *choice, char *final);
int						change_back(t_env *e);
void					refill_path(t_env **e);
void					actualise_env_tab(t_env **e, char **env);

int						change_env(t_env *e, char ***args);
char					**change_env_decoupage(char **args, int saut);
int						change_env_error(char **args);

char					**change_env_i(t_env **e, char **args);
char					**change_env_u(t_env **e, char **args);
int						reverse_datacpy(t_env **e);

int						change_env_error(char **args);

void					change_directory(t_env *e, char **args, char *line);
int						go_to_home(t_env *e, char **args);

int						cd_default(t_env *e, char **args, int i);
int						cd_physical(t_env *e, char **args, int i);
int						cd_back(t_env *e);
char					*change_to_home(t_env *e, char *str);

int						cd_not_found(char *line);
int						cd_error(char *final);

t_env					*create_env(char **env);
int						add_back_data(t_env **env, char *content, char *prefix);
int						add_back_cpy(t_env **env, char *content, char *prefix);
t_data					*create_data(char *content, char *prefix);

void					malloc_handling(void);
int						error_path_not_found(char *str, char *line);
char					*error_handler(char *tmp);
char					*error_not_found(char *line);
int						get_name(char *line);

char					*error_exe(char *tmp);
int						error_no_exec(char *tmp);

int						display_env(t_env *e);
void					display_prompt(t_env *e);
void					ft_putstr_path_color(char *str);

void					free_args(char **args);
void					free_env(t_env **e);
void					free_data(t_data **lst);
void					free_env_tab(char **env);

int						shlvl(char **suffix);
int						suite_get_all_function(t_env *e, char **args);

int						loop_prompt(t_env *data_env);

#endif
