# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ishafie <ishafie@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/04/25 23:31:13 by ishafie           #+#    #+#              #
#    Updated: 2016/05/26 00:21:58 by ishafie          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=		quadtree
SRC			=		main.c 
					
					
OBJ_NAME	=		$(SRC:.c=.o)
OBJ_PATH	=		obj/
OBJ			=		$(addprefix $(OBJ_PATH), $(OBJ_NAME))
FLAGS		=		-Wall -Wextra -Werror --ansi --pedantic 
LIB			=		-lMLV 

.PHONY: all, clean, fclean, re

$(NAME): $(OBJ)
	gcc -o $(NAME) $(FLAGS) $(OBJ) $(LIB) 

all: $(NAME)

$(OBJ_PATH)%.o: %.c
	@mkdir -p obj
	gcc $(FLAGS) -c $< -o $@ $(LIB)  -I includes

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -rf $(NAME)

re: fclean all