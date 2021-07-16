# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edavid <edavid@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/07 16:17:01 by edavid            #+#    #+#              #
#    Updated: 2021/07/16 19:13:41 by edavid           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = a.out
CC = gcc
OBJ = driver.o ft_colors.o ft_utils.o ft_hooks.o ft_get_next_line.o \
ft_get_next_line_utils.o ft_error.o ft_image_initialize.o ft_utils2.o \
ft_utils3.o ft_move_ninja.o ft_patrol_enemy_helper.o ft_utils4.o \
ft_utils5.o ft_utils6.o ft_utils7.o
CFLAGS = -Wall -Wextra -Werror
BFLAG = -D BONUS

$(NAME): $(OBJ)
	cd mlx_linux && $(MAKE) re
	cp ./mlx_linux/libmlx.a .
	mv libmlx.a libsolong.a
	cd libft && $(MAKE) all
	cp ./libft/libft.a .
	ar -x libft.a
	ar -rs libsolong.a *.o
	rm -f libft.a
	mv libsolong.a libr/
	$(CC) -lz -L/usr/lib -Imlx_linux -lXext -lX11 -lm -o $(NAME) -Llibr -lsolong
# -lz flag is for zlib, which mlx_png_file_to_image uses
test: $(OBJ)
%.o: %.c
	$(CC) -g $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@
ft_utils.o: ft_utils.c ft_utils.h mlx_linux/mlx.h libft/libft.h
	$(CC) -g $(CFLAGS) -Imlx -c ft_utils.c -o $@
ft_get_next_line.o: gnl/ft_get_next_line.c gnl/ft_get_next_line.h
	$(CC) -g $(CFLAGS) -c gnl/ft_get_next_line.c
ft_get_next_line_utils.o: gnl/ft_get_next_line_utils.c gnl/ft_get_next_line.h
	$(CC) -g $(CFLAGS) -c gnl/ft_get_next_line_utils.c
.PHONY: all clean fclean re bonus
clean:
	cd mlx_linux && rm -f *.o a.out
	rm -f *.o a.out
	cd libft && rm -f *.o a.out 
re:
	make clean
	make all
all: $(NAME)
fclean: clean
	rm -f *.a
	cd libft && rm -f *.a
	cd mlx_linux && rm -f *.a
bonus: clean
bonus: CFLAGS += $(BFLAG)
bonus: test
bonus: all
