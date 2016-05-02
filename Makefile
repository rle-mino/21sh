# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/04/25 23:31:13 by rle-mino          #+#    #+#              #
#    Updated: 2016/05/02 17:09:56 by ishafie          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=				21sh

SRC		=				actualise_env.c 			\
						change_directory.c			\
						change_directory_action.c	\
						change_directory_error.c	\
						change_env.c				\
						change_env_error.c			\
						change_env_flag.c			\
						check.c						\
						display.c					\
						display_line.c				\
						edit_line.c					\
						error.c						\
						error_rwx.c					\
						free_memory.c				\
						ft_putint.c					\
						get.c						\
						get_env_var.c				\
						history.c					\
						init_term.c					\
						main.c						\
						minishell.c					\
						move.c						\
						move2.c						\
						multi_command.c				\
						my_exit.c					\
						my_set_env.c				\
						parsing.c					\
						parsing_arg.c				\
						set_env_error.c				\
						signal_fnt.c				\
						struct.c					\
						term_error.c				\
						to_is.c						\
						tools.c						\


OBJ		=				$(SRC:.c=.o)

FLAGS	=				-Wall -Wextra -Werror

.PHONY: all, clean, fclean, re

$(NAME): $(OBJ)
	make -C libft
	gcc -o $(NAME) $(FLAGS) -lcurses $(OBJ) -lft -L ./libft -I includes

all: $(NAME)

%.o: %.c
	gcc -c $< -o $@ -I includes $(FLAGS)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
