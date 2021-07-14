/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 10:02:09 by edavid            #+#    #+#             */
/*   Updated: 2021/07/14 15:22:04 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "mlx/mlx.h"
#include "ft_hooks.h"
#include "ft_colors.h"
#include "ft_basic_shapes.h"
#include "ft_utils.h"
#include "libft/libft.h"

int	key_hook(int keycode, t_vars *vars)
{
	(void)vars;
	printf("keycode: %d\n", keycode);
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	mouse_hook(int button, int x, int y, t_vars *vars)
{
	(void)vars;
	printf("mouse btn: %d x: %d y: %d\n", button, x, y);
	return (0);
}

static int	wasd_pressed(int keycode, int *x, int *y, int *prev_x, int *prev_y)
{
	int	step;

	step = 20;
	if (keycode == 13)
	{
		*prev_x = *x;
		*prev_y = *y;
		*y -= step;
		return (1);
	}
	else if (keycode == 0)
	{
		*prev_x = *x;
		*prev_y = *y;
		*x -= step;
		return (1);
	}
	else if (keycode == 1)
	{
		*prev_x = *x;
		*prev_y = *y;
		*y += step;
		return (1);
	}
	else if (keycode == 2)
	{
		*prev_x = *x;
		*prev_y = *y;
		*x += step;
		return (1);
	}
	return (0);
}

static int	wasd_pressed2(int keycode, t_point *cur_pos, int *prev_x, int *prev_y, int map_width, int map_height, char ***map, int *move_counter)
{
	if (keycode == 13) // W
	{
		*prev_x = cur_pos->x;
		*prev_y = cur_pos->y;
		if (*prev_y - 1 < 0)
			return (0);
		if (*(*(*map + *prev_y - 1) + *prev_x) == '1')
			return (0);
		(cur_pos->y)--;
		(*move_counter)++;
		return (1);
	}
	else if (keycode == 0) // A
	{
		*prev_x = cur_pos->x;
		*prev_y = cur_pos->y;
		if (*prev_x - 1 < 0)
			return (0);
		if (*(*(*map + *prev_y) + *prev_x - 1) == '1')
			return (0);
		(cur_pos->x)--;
		(*move_counter)++;
		return (1);
	}
	else if (keycode == 1) // S
	{
		*prev_x = cur_pos->x;
		*prev_y = cur_pos->y;
		if (*prev_y + 1 > map_height)
			return (0);
		if (*(*(*map + *prev_y + 1) + *prev_x) == '1')
			return (0);
		(cur_pos->y)++;
		(*move_counter)++;
		return (1);
	}
	else if (keycode == 2) // D
	{
		*prev_x = cur_pos->x;
		*prev_y = cur_pos->y;
		if (*prev_x + 1 > map_width)
			return (0);
		if (*(*(*map + *prev_y) + *prev_x + 1) == '1')
			return (0);
		(cur_pos->x)++;
		(*move_counter)++;
		return (1);
	}
	return (0);
}

int		move_circle(int keycode, t_mystruct *mystruct)
{
	int	radius;
	radius = 85;
	
	// only do this on keypress, w = 13, a = 0, s = 1, d = 2
	if (wasd_pressed(keycode, mystruct->x, mystruct->y, mystruct->prev_x, mystruct->prev_y))
	{
		circle_put_parametric(mystruct->img, *mystruct->prev_x, *mystruct->prev_y, radius, mlx_black.value);
		circle_put_parametric(mystruct->img, *mystruct->x, *mystruct->y, radius, -1);
		mlx_put_image_to_window(mystruct->vars->mlx, mystruct->vars->win, mystruct->img->img, 0, 0);
	}
	return (0);
}

static int	all_collected(char ***map, int width, int height)
{
	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
			if (*(*(*map + y) + x) == 'C')
				return (0);
	return (1);
}

int		move_ninja(int keycode, t_mystruct2 *mystruct)
{
	int			cur_line_counter;
	char		cur_c;
	char		prev_c;
	int			is_all_collected;
	static int	movement_state;

	if (keycode == 53)
	{
		mlx_destroy_window(mystruct->vars->mlx, mystruct->vars->win);
		cur_line_counter = 0;
		while (cur_line_counter < mystruct->map_height)
			free(*(*mystruct->map + cur_line_counter++));
		free(*mystruct->map);
		free(mystruct->images);
		free(mystruct->numberImages);
		exit(EXIT_SUCCESS);
	}
	if (wasd_pressed2(keycode, mystruct->cur_position, mystruct->prev_x, mystruct->prev_y, mystruct->map_width, mystruct->map_height, mystruct->map, mystruct->move_counter))
	{
		cur_c = *(*((*mystruct->map) + mystruct->cur_position->y) + mystruct->cur_position->x);
		prev_c = *(*((*mystruct->map) + *mystruct->prev_y) + *mystruct->prev_x);
		mlx_put_image_to_window(mystruct->vars->mlx, mystruct->vars->win, mystruct->images[4].img, *mystruct->prev_x * CELL_SIZE_W, *mystruct->prev_y * CELL_SIZE_H);
		if (prev_c == 'Q')
			mlx_put_image_to_window(mystruct->vars->mlx, mystruct->vars->win, mystruct->images[2].img, *mystruct->prev_x * CELL_SIZE_W, *mystruct->prev_y * CELL_SIZE_H);
		if (cur_c == 'C')
		{
			mlx_put_image_to_window(mystruct->vars->mlx, mystruct->vars->win, mystruct->images[4].img, mystruct->cur_position->x * CELL_SIZE_W, mystruct->cur_position->y * CELL_SIZE_H);
			*(*((*mystruct->map) + *mystruct->prev_y) + *mystruct->prev_x) = '0';
			*(*((*mystruct->map) + mystruct->cur_position->y) + mystruct->cur_position->x) = 'P';
		}
		is_all_collected = all_collected(mystruct->map, mystruct->map_width, mystruct->map_height);
		if (cur_c == 'E' && is_all_collected) // end of game condition, then ex. initialize map again
		{
			reset_map(mystruct);
			movement_state = 0;
			return (0);
		}
		else
		{
			printf("move counter: %d\n", *mystruct->move_counter);
			number_put(*mystruct->move_counter, 600, 600, mystruct, *mystruct->move_counter - 1);
			if (++movement_state == 8)
				movement_state = 0;
			mlx_put_image_to_window(mystruct->vars->mlx, mystruct->vars->win, (mystruct->playerMovement + movement_state)->img, mystruct->cur_position->x * CELL_SIZE_W, mystruct->cur_position->y * CELL_SIZE_H);
			if (prev_c == 'Q')
				*(*((*mystruct->map) + *mystruct->prev_y) + *mystruct->prev_x) = 'E';
			else
				*(*((*mystruct->map) + *mystruct->prev_y) + *mystruct->prev_x) = '0';
			if (cur_c == 'E')
				*(*((*mystruct->map) + mystruct->cur_position->y) + mystruct->cur_position->x) = 'Q';
			else
				*(*((*mystruct->map) + mystruct->cur_position->y) + mystruct->cur_position->x) = 'P';
		}
	}
	return (0);
}

int	exit_clicked(t_mystruct2 *mystruct)
{
	int	cur_line_counter;

	mlx_destroy_window(mystruct->vars->mlx, mystruct->vars->win);
	cur_line_counter = 0;
	while (cur_line_counter < mystruct->map_height)
		free(*(*mystruct->map + cur_line_counter++));
	free(*mystruct->map);
	free(mystruct->images);
	free(mystruct->numberImages);
	exit(EXIT_SUCCESS);
}

static int	count_collectibles(t_mystruct2 *mystruct)
{
	int	counter;

	counter = 0;
	for (int y = 0; y < mystruct->map_height + 2; y++)
		for (int x = 0; x < mystruct->map_width + 2; x++)
			if (*(*(*mystruct->map + y) + x) == 'C')
				counter++;
	return (counter);
}

static void	initialize_positions(t_mystruct2 *mystruct, t_point **positions, int number_of_enemies)
{
	int	cur_index;

	*positions = malloc(number_of_enemies * sizeof(**positions));
	cur_index = 0;
	for (int y = 0; y < mystruct->map_height + 2; y++)
		for (int x = 0; x < mystruct->map_width + 2; x++)
			if (*(*(*mystruct->map + y) + x) == 'C')
				*(*positions + cur_index++) = (t_point){x, y};
}

#define IS_MOVING_UP (previous_position->y - 1 == current_position->y)
#define IS_MOVING_LEFT (previous_position->x - 1 == current_position->x)
#define IS_MOVING_DOWN (previous_position->y + 1 == current_position->y)
#define IS_MOVING_RIGHT (previous_position->x + 1 == current_position->x)
#define UP_CHAR (*(*((*mystruct->map) + current_position->y - 1) + current_position->x))
#define LEFT_CHAR (*(*((*mystruct->map) + current_position->y) + current_position->x - 1))
#define DOWN_CHAR (*(*((*mystruct->map) + current_position->y + 1) + current_position->x))
#define RIGHT_CHAR (*(*((*mystruct->map) + current_position->y) + current_position->x + 1))

static void	get_next_position(t_mystruct2 *mystruct, t_point *current_position, t_point *previous_position)
{
	t_node	neighbour_chars[4] = {
		{UP_CHAR, "up_char", 0},
		{LEFT_CHAR, "left_char", 0},
		{DOWN_CHAR, "down_char", 0},
		{RIGHT_CHAR, "right_char", 0}
	};
	t_node	*cur_node;
	int		i;
	char	*str;

	neighbour_chars[0].next = &neighbour_chars[1];
	neighbour_chars[1].next = &neighbour_chars[2];
	neighbour_chars[2].next = &neighbour_chars[3];
	neighbour_chars[3].next = &neighbour_chars[0];
	// printf("New position: %d %d\n", current_position->x, current_position->y);
	// printf("Previous position: %d %d\n", previous_position->x, previous_position->y);
	// printf("%c %c %c %c\n", UP_CHAR, LEFT_CHAR, DOWN_CHAR, RIGHT_CHAR);
	// printf("Move: %d %d %d %d\n", IS_MOVING_UP, IS_MOVING_LEFT, IS_MOVING_DOWN, IS_MOVING_RIGHT);
	// printf("Cur, prev position: %d %d %d %d\n", current_position->x, current_position->y, previous_position->x, previous_position->y);
	// printf("Chars: %c %c %c %c\n", UP_CHAR, LEFT_CHAR, DOWN_CHAR, RIGHT_CHAR);
	if (IS_MOVING_UP)
		cur_node = &neighbour_chars[0];
	else if (IS_MOVING_LEFT)
		cur_node = &neighbour_chars[1];
	else if (IS_MOVING_DOWN)
		cur_node = &neighbour_chars[2];
	else if (IS_MOVING_RIGHT)
		cur_node = &neighbour_chars[3];
	else
		cur_node = &neighbour_chars[0];
	i = -1;
	while (++i < 4 && cur_node->value == '1')
		cur_node = cur_node->next;
	// printf("i: %d\n", i);
	if (i != 4) // in not in-between 4 walls
	{
		*previous_position = *current_position;
		str = cur_node->name;
		if (!ft_strncmp(str, "up_char", 2))
			current_position->y -= 1;
		else if (!ft_strncmp(str, "left_char", 2))
			current_position->x -= 1;
		else if (!ft_strncmp(str, "down_char", 2))
			current_position->y += 1;
		else // right_char
			current_position->x += 1;
	}
	// printf("new position: %d %d\n\n", current_position->x, current_position->y);
}

static void	initialize_vars(t_point **enemy_positions, t_point **enemy_previous_positions,
int *number_of_enemies)
{
	
}

int	patrol_enemy(t_mystruct2 *mystruct)
{
	static t_point	*enemy_positions;
	static t_point	*enemy_previous_positions;
	static int		number_of_enemies;
	static int		number_of_calls;

	if (!enemy_previous_positions) // initialize
	{
		number_of_enemies = count_collectibles(mystruct);
		initialize_positions(mystruct, &enemy_positions, number_of_enemies);
		enemy_previous_positions = malloc(number_of_enemies * sizeof(*enemy_previous_positions));
		for (int i = 0; i < number_of_enemies; i++)
		{
			enemy_previous_positions[i].x = enemy_positions[i].x;
			enemy_previous_positions[i].y = enemy_positions[i].y + 1;
		}
	}
	if (number_of_calls == 9999)
	{
		for (int i = 0; i < number_of_enemies; i++)
		{
			//printf("enemy %d\n", i + 1);
			// set next and previous positions in vars
			get_next_position(mystruct, enemy_positions + i, enemy_previous_positions + i);
			//printf("enemy %d position: %d %d\n", i, enemy_positions[i].x, enemy_positions[i].y);
			// set new position on map
			if (*(*(*mystruct->map + enemy_positions[i].y) + enemy_positions[i].x) == 'P') // game over
			{
				free(enemy_positions);
				free(enemy_previous_positions);
				enemy_positions = 0;
				enemy_previous_positions = 0;
				number_of_calls = 0;
				number_of_enemies = 0;
				reset_map(mystruct);
				return (0);
			}
			*(*(*mystruct->map + enemy_previous_positions[i].y) + enemy_previous_positions[i].x) = '0';
			*(*(*mystruct->map + enemy_positions[i].y) + enemy_positions[i].x) = 'C';
			// draw changes
			mlx_put_image_to_window(mystruct->vars->mlx, mystruct->vars->win, (mystruct->images + 4)->img,
				(enemy_previous_positions + i)->x * CELL_SIZE_W, (enemy_previous_positions + i)->y * CELL_SIZE_W);
			mlx_put_image_to_window(mystruct->vars->mlx, mystruct->vars->win, (mystruct->images + 3)->img,
				(enemy_positions + i)->x * CELL_SIZE_W, (enemy_positions + i)->y * CELL_SIZE_W);
		}
		print_map(mystruct);
		printf("\n\n");
	}
	number_of_calls++;
	if (number_of_calls == 10000)
		number_of_calls = 0;
	return (0);
}
