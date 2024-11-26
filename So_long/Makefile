# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybiloshy <ybiloshy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/09 18:04:30 by ybiloshy          #+#    #+#              #
#    Updated: 2024/11/25 18:27:57 by ybiloshy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

LIBFT = ./libraries/Libft/libft.a
GNL = ./libraries/Get_next_line/get_next_line.a
FT_PRINTF = ./libraries/ft_printf/libftprintf.a

LIB_DIRS = -L./libraries/minilibx -L./libraries/Libft -L./libraries/Get_next_line -L./libraries/ft_printf
LIBS = -lmlx -lft -lXext -lX11 -lget_next_line -lftprintf

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -I./libraries/minilibx -I./libraries/Libft -I./sources -I./libraries/Get_next_line -I./libraries/ft_printf
LDFLAGS = $(LIB_DIRS) $(LIBS)
SRCS_DIR = ./sources/
OBJ_DIR = build

SRCS 			= $(addprefix $(SRCS_DIR),\
						main.c \
						game.c \
						map.c \
						map_parser.c \
						checkers.c \
						hey_hook.c \
						free.c \
						error.c )

OBJS			= $(addprefix $(OBJ_DIR)/, \
						main.o \
						game.o \
						map.o \
						map_parser.o \
						checkers.o \
						hey_hook.o \
						free.o \
						error.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(GNL) $(FT_PRINTF)
	$(CC) $(OBJS) $(LIBFT) $(GNL) $(FT_PRINTF) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C libraries/Libft

$(GNL):
	make -C libraries/Get_next_line

$(FT_PRINTF):
	make -C libraries/ft_printf

clean:
	rm -f $(OBJS)
	make clean -C libraries/Libft
	make clean -C libraries/Get_next_line
	make clean -C libraries/ft_printf

fclean: clean
	rm -f $(NAME)
	make fclean -C libraries/Libft
	make fclean -C libraries/Get_next_line
	make fclean -C libraries/ft_printf

re: fclean all

.PHONY: all clean fclean re
