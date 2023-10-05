# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eabdelha <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/27 10:10:17 by eabdelha          #+#    #+#              #
#    Updated: 2021/12/28 17:45:21 by eabdelha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
NAME_LIBFT = libft.a
MLX = -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit

MLX_INCLUDE = /usr/local/include
INCLUDE = ./src_man/so_long.h
BINCLUDE = ./src_bonus/so_long_bonus.h

LIBFT_PATH = ./libft
SRC_PATH = ./src_man
BSRC_PATH = ./src_bonus

CC = gcc
CFLAGS = -Wall -Wextra -Werror

BSRC =  ./src_bonus/so_long_bonus.c     \
		./src_bonus/so_long_utils_bonus.c      \
		./src_bonus/read_map_bonus.c	\
		./src_bonus/display_bonus.c	\
		./src_bonus/enemy_move_bonus.c

SRC =  	./src_man/so_long.c         \
        ./src_man/so_long_utils.c		\
		./src_man/read_map.c \
		./src_man/display.c

.PHONY : all bonus clean fclean re

all: $(NAME)

bonus : $(BINCLUDE) $(MLX_INCLUDE)
	@make -C $(LIBFT_PATH)
	@$(CC) $(CFLAGS) $(BSRC) $(LIBFT_PATH)/$(NAME_LIBFT) $(MLX) -o $(BSRC_PATH)/$(NAME)

$(NAME): $(INCLUDE) $(MLX_INCLUDE)
	@make -C $(LIBFT_PATH)
	@$(CC) $(CFLAGS) $(SRC) $(LIBFT_PATH)/$(NAME_LIBFT) $(MLX) -o $(SRC_PATH)/$(NAME)

clean:
	@make clean -C $(LIBFT_PATH)

fclean: clean
	@make fclean -C $(LIBFT_PATH) 
	@rm -rf $(BSRC_PATH)/$(NAME) $(SRC_PATH)/$(NAME)

re: fclean all

