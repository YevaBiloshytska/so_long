# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybiloshy <nikolly19.12@gmail.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/09 18:04:30 by ybiloshy          #+#    #+#              #
#    Updated: 2024/11/13 23:00:35 by ybiloshy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
LIBFT = ./libraries/Libft/libft.a
//GNL = ./libraries/Get_next_line/get_next_line.a  # Путь к библиотеке get_next_line


CC = gcc
CFLAGS = -Wall -Werror -Wextra -I. -I./libraries/minilibx -I./libraries/Libft -I./libraries/get_next_line -arch arm64
LDFLAGS = -L./libraries/minilibx -lmlx -L./libraries/Libft -lft -L./libraries/get_next_line -lget_next_line -arch arm64 -framework OpenGL -framework AppKit

SRCS_DIR		= ./sources/

SRCS 			= $(addprefix $(SRCS_DIR),\
						main.c \
						game.c \
						map.c \
						map_parser.c)

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(GNL) 
	$(CC) $(OBJS) $(LIBFT) $(GNL) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	make -C libraries/Libft

$(GNL):  # Правила для сборки библиотеки get_next_line
	make -C libraries/get_next_line

clean:
	rm -f $(OBJS)
	make clean -C libraries/Libft
	make clean -C libraries/get_next_line  # Чистим get_next_line

fclean: clean
	rm -f $(NAME)
	make fclean -C libraries/Libft
	make fclean -C libraries/get_next_line  # Чистим get_next_line

re: fclean all

.PHONY: all clean fclean re