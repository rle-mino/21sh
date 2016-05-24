# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/04/25 23:31:13 by rle-mino          #+#    #+#              #
#    Updated: 2016/05/24 22:25:26 by rle-mino         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=				21sh

SRC			=				actualise_env.c							\
							buffer_parse.c							\
							change_directory.c						\
							change_directory_action.c				\
							change_directory_error.c				\
							change_env.c							\
							change_env_error.c						\
							change_env_flag.c						\
							check.c									\
							command_edit.c							\
							command_free.c							\
							create_command.c						\
							display.c								\
							display_line.c							\
							edit_line.c								\
							edit_line_pairing.c						\
							error.c									\
							error_rwx.c								\
							free_memory.c							\
							free_memory2.c							\
							ft_putint.c								\
							get.c									\
							get2.c									\
							get_clipboard.c							\
							get_env_var.c							\
							auto_complete.c							\
							space_between_redir.c					\
							get_next_line.c							\
							history.c								\
							history2.c								\
							heredoc.c								\
							heredoc2.c								\
							init_term.c								\
							line.c									\
							leaks.c									\
							main.c									\
							minishell.c								\
							move.c									\
							move2.c									\
							multi_command.c							\
							my_exit.c								\
							my_set_env.c							\
							pairing.c								\
							parsing.c								\
							parsing_arg.c							\
							pipe.c									\
							redirection.c							\
							redirection2.c							\
							redirection3.c							\
							redirection_error.c						\
							set_env_error.c							\
							signal_fnt.c							\
							struct.c								\
							tabulation_tree.c						\
							tabulation_tree_display.c				\
							tabulation_tree_action.c				\
							term_error.c							\
							to_is.c									\
							tools.c									\


OBJ_NAME	=		$(SRC:.c=.o)
OBJ_PATH	=		obj/
OBJ			=		$(addprefix $(OBJ_PATH), $(OBJ_NAME))

FLAGS		=		-Wall -Wextra -Werror

.PHONY: all, clean, fclean, re

$(NAME): $(OBJ)
	make -C libft
	gcc -o $(NAME) $(FLAGS) -lcurses $(OBJ) -lft -L ./libft -I includes

all: $(NAME)

$(OBJ_PATH)%.o: %.c
	@mkdir -p obj
	gcc -c $< -o $@ -I includes $(FLAGS)

clean:
	make -C libft/ fclean
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -rf $(NAME)

re: fclean all
