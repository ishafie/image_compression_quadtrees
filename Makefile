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
SRC			=		main.c				\
					image_action.c		\
					quadtree_action.c	\
					quadtree_creation.c	\
					err.c				\
					distance.c			\
					encodage.c			\
					decodage.c			\
					lst_add_order.c		\
					minimisation.c		\
					encodage_graph.c	\
					decodage_graph.c	\
					list_encoding.c		\
					get_next_line.c		\

OBJ_NAME	=		$(SRC:.c=.o)
OBJ_PATH	=		obj/
OBJ			=		$(addprefix $(OBJ_PATH), $(OBJ_NAME))
FLAGS		=		-Wall -Wextra -Werror --ansi --pedantic  -g -D_REENTRANT
LIB			=		-lMLV -lm -lpthread

.PHONY: all, clean, fclean, re

$(NAME): $(OBJ)
	gcc -o $(NAME) $(FLAGS) $(OBJ) $(LIB)

all: $(NAME)

$(OBJ_PATH)%.o: %.c
	@mkdir -p obj
	gcc $(FLAGS) -c $< -o $@ $(LIB)

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -rf $(NAME)

re: fclean all
