# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybiloshy <ybiloshy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/09 18:04:30 by ybiloshy          #+#    #+#              #
#    Updated: 2024/11/23 14:54:08 by ybiloshy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

LIBFT = ./libraries/Libft/libft.a
GNL = ./libraries/Get_next_line/get_next_line.a

LIB_DIRS = -L./libraries/minilibx -L./libraries/Libft -L./libraries/Get_next_line
LIBS = -lmlx -lft -lXext -lX11 -lget_next_line

CC = gcc
CFLAGS = -Wall -Werror -Wextra -I./libraries/minilibx -I./libraries/Libft -I./sources -I./libraries/Get_next_line
LDFLAGS = $(LIB_DIRS) $(LIBS)
SRCS_DIR		= ./sources/
SRCS 			= $(addprefix $(SRCS_DIR),\
						main.c \
						game.c \
						map.c \
						map_parser.c \
						checkers.c \
						hey_hook.c \
						free.c \
						error.c )

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(GNL) 
	$(CC) $(OBJS) $(LIBFT) $(GNL) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	make -C libraries/Libft

$(GNL):
	make -C libraries/Get_next_line

clean:
	rm -f $(OBJS)
	make clean -C libraries/Libft
	make fclean -C libraries/Get_next_line


fclean: clean
	rm -f $(NAME)
	make fclean -C libraries/Libft
	make fclean -C libraries/Get_next_line


re: fclean all

.PHONY: all clean fclean re
