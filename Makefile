# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edavid <edavid@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/07 16:17:01 by edavid            #+#    #+#              #
#    Updated: 2021/07/14 18:12:36 by edavid           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = a.out
CC = gcc
OBJ = driver.o ft_basic_shapes.o ft_colors.o ft_utils.o ft_hooks.o ft_testers.o ft_get_next_line.o \
ft_get_next_line_utils.o ft_error.o
CFLAGS = -Wall -Wextra -Werror
BFLAG = -D BONUS

$(NAME): $(OBJ)
	cd libft && $(MAKE) all
	cp ./libft/libft.a .
	mv libft.a libsolong.a
	ar -rs libsolong.a $(OBJ)
	$(CC) -lz -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME) $(OBJ) -Llibft -lft
# -lz flag is for zlib, which mlx_png_file_to_image uses
%.o: %.c
	$(CC) -g $(CFLAGS) -Imlx -c $< -o $@
ft_utils.o: ft_utils.c ft_utils.h mlx/mlx.h libft/libft.h
	$(CC) -g $(CFLAGS) -Imlx -c ft_utils.c -o $@
ft_get_next_line.o: gnl/ft_get_next_line.c gnl/ft_get_next_line.h
	$(CC) -g $(CFLAGS) -c gnl/ft_get_next_line.c
ft_get_next_line_utils.o: gnl/ft_get_next_line_utils.c gnl/ft_get_next_line.h
	$(CC) -g $(CFLAGS) -c gnl/ft_get_next_line_utils.c
.PHONY: all clean fclean re bonus
clean:
	rm -f *.o a.out
re:
	make clean
	make all
all: $(NAME)
fclean: clean
	rm -f *.a
bonus: clean
bonus: CFLAGS += $(BFLAG)
bonus: all
