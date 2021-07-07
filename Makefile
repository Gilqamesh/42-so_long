# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edavid <edavid@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/07 16:17:01 by edavid            #+#    #+#              #
#    Updated: 2021/07/07 16:17:02 by edavid           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = a.out
CC = gcc
OBJ = driver.o ft_basic_shapes.o ft_colors.o ft_utils.o

$(NAME): $(OBJ)
	$(CC) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME) $(OBJ)
%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@
.PHONY: all clean fclean re bonus
