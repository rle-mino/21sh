# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/04/25 23:31:13 by rle-mino          #+#    #+#              #
#    Updated: 2016/04/26 05:25:59 by ishafie          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=				21sh

SRC		=				main.c			\
						edit_line.c		\
						get.c			\
						ft_putint.c		\
						to_is.c			\
						move.c			\
						init_term.c		\
						term_error.c	\

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
