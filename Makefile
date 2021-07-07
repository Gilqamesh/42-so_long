NAME = a.out
CC = gcc
OBJ = driver.o

$(NAME): $(OBJ)
	$(CC) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME) $(OBJ)
%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@
.PHONY: all clean fclean re bonus
