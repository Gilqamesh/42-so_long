/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 10:02:09 by edavid            #+#    #+#             */
/*   Updated: 2021/07/16 13:34:41 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "mlx/mlx.h"
#include "ft_hooks.h"
#include "ft_colors.h"
#include "ft_utils.h"
#include "libft/libft.h"
#include "ft_structs.h"

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

static int	all_collected(char ***map, int width, int height)
{
	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
			if (*(*(*map + y) + x) == 'C')
				return (0);
	return (1);
}

int		move_ninja(int keycode, t_mystruct *mystruct)
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
		free(mystruct->map);
		free(mystruct->all_images.images);
		free(mystruct->all_images.numberImages);
		exit(EXIT_SUCCESS);
	}
	if (wasd_pressed2(keycode, mystruct->cur_position, mystruct->prev_x, mystruct->prev_y, mystruct->map_width, mystruct->map_height, mystruct->map, mystruct->move_counter))
	{
		cur_c = *(*(*mystruct->map + mystruct->cur_position->y) + mystruct->cur_position->x);
		prev_c = *(*(*mystruct->map + *mystruct->prev_y) + *mystruct->prev_x);
		mlx_put_image_to_window(mystruct->vars->mlx, mystruct->vars->win, (mystruct->all_images.images + 4)->img, *mystruct->prev_x * CELL_SIZE_W, *mystruct->prev_y * CELL_SIZE_H);
		if (prev_c == 'Q')
			mlx_put_image_to_window(mystruct->vars->mlx, mystruct->vars->win, (mystruct->all_images.images + 2)->img, *mystruct->prev_x * CELL_SIZE_W, *mystruct->prev_y * CELL_SIZE_H);
		if (cur_c == 'C')
		{
			mlx_put_image_to_window(mystruct->vars->mlx, mystruct->vars->win, (mystruct->all_images.images + 4)->img, mystruct->cur_position->x * CELL_SIZE_W, mystruct->cur_position->y * CELL_SIZE_H);
			*(*((*mystruct->map) + *mystruct->prev_y) + *mystruct->prev_x) = '0';
			*(*((*mystruct->map) + mystruct->cur_position->y) + mystruct->cur_position->x) = 'P';
		}
		if (IS_BONUS)
			is_all_collected = 1;
		else
			is_all_collected = all_collected(mystruct->map, mystruct->map_width, mystruct->map_height);
		if (cur_c == 'E' && is_all_collected) // end of game condition, then ex. initialize map again
		{
			reset_map(mystruct);
			*mystruct->need_reset = 1;
			patrol_enemy(mystruct);
			*mystruct->need_reset = 0;
			movement_state = 0;
			return (0);
		}
		else
		{
			if (IS_BONUS)
				number_put(*mystruct->move_counter, (t_point){600, 600}, mystruct, *mystruct->move_counter - 1);
			else
				printf("move counter: %d\n", *mystruct->move_counter);
			if (++movement_state == 8)
				movement_state = 0;
			mlx_put_image_to_window(mystruct->vars->mlx, mystruct->vars->win, (mystruct->all_images.playerMovement + movement_state)->img, mystruct->cur_position->x * CELL_SIZE_W, mystruct->cur_position->y * CELL_SIZE_H);
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

int	exit_clicked(t_mystruct *mystruct)
{
	int	cur_line_counter;

	mlx_destroy_window(mystruct->vars->mlx, mystruct->vars->win);
	cur_line_counter = 0;
	while (cur_line_counter < mystruct->map_height)
		free(*(*mystruct->map + cur_line_counter++));
	free(mystruct->map);
	free(mystruct->all_images.images);
	free(mystruct->all_images.numberImages);
	exit(EXIT_SUCCESS);
}

static int	count_collectibles(t_mystruct *mystruct)
{
	int	counter;

	counter = 0;
	for (int y = 0; y < mystruct->map_height; y++)
		for (int x = 0; x < mystruct->map_width; x++)
			if (*(*(*mystruct->map + y) + x) == 'C')
				counter++;
	return (counter);
}

static void	initialize_positions(t_mystruct *mystruct, t_point **positions, int number_of_enemies)
{
	int	cur_index;

	*positions = malloc(number_of_enemies * sizeof(**positions));
	cur_index = 0;
	for (int y = 0; y < mystruct->map_height; y++)
		for (int x = 0; x < mystruct->map_width; x++)
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

// remember last move, cant go back
// each step check for previous move in linked list if it can be made
static void	get_next_position(t_mystruct *mystruct, t_point *current_position, t_point *previous_position)
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
		cur_node = &neighbour_chars[3];
	else if (IS_MOVING_LEFT)
		cur_node = &neighbour_chars[0];
	else if (IS_MOVING_DOWN)
		cur_node = &neighbour_chars[1];
	else if (IS_MOVING_RIGHT)
		cur_node = &neighbour_chars[2];
	else
		cur_node = &neighbour_chars[0];
	i = -1;
	while (++i < 5 && cur_node->value == '1')
		cur_node = cur_node->next;
	// printf("i: %d\n", i);
	if (i != 5) // in not in-between 4 walls
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

static void	get_exit_coords(t_mystruct *mystruct, t_point *exit)
{
	for (int y = 0; y < mystruct->map_height; y++)
		for (int x = 0; x < mystruct->map_width; x++)
			if (*(*(*mystruct->map + y) + x) == 'E')
			{
				exit->x = x;
				exit->y = y;
				return ;
			}
}

static void	initialize_vars(t_point **enemy_positions, t_point **enemy_previous_positions,
int *number_of_enemies, t_point *exit, t_mystruct *mystruct)
{
	get_exit_coords(mystruct, exit);
	*number_of_enemies = count_collectibles(mystruct);
	initialize_positions(mystruct, enemy_positions, *number_of_enemies);
	*enemy_previous_positions = malloc(*number_of_enemies * sizeof(*enemy_previous_positions));
	for (int i = 0; i < *number_of_enemies; i++)
	{
		(*enemy_previous_positions)[i].x = (*enemy_positions)[i].x + 1;
		(*enemy_previous_positions)[i].y = (*enemy_positions)[i].y;
	}
}

int	patrol_enemy(t_mystruct *mystruct)
{
	static t_point	exit;
	static t_point	*enemy_positions;
	static t_point	*enemy_previous_positions;
	static int		number_of_enemies;
	static int		number_of_calls;

	if (*mystruct->need_reset || !number_of_calls) // initialize
	{
		initialize_vars(&enemy_positions, &enemy_previous_positions, &number_of_enemies, &exit, mystruct);
		//printf("hey\n");
	}
	if (number_of_calls == 9999)
	{
		for (int i = 0; i < number_of_enemies; i++) // delete previous position of all
		{
			//printf("enemy %d\n", i + 1);
			// set next and previous positions in vars
			get_next_position(mystruct, enemy_positions + i, enemy_previous_positions + i);
			//printf("enemy %d position: %d %d\n", i, enemy_positions[i].x, enemy_positions[i].y);
			// set new position on map
			// G - player + enemy
			// Q - enemy + exit
			*(*(*mystruct->map + enemy_previous_positions[i].y) + enemy_previous_positions[i].x) = '0';
			if (*(*(*mystruct->map + enemy_positions[i].y) + enemy_positions[i].x) == 'P')
				*(*(*mystruct->map + enemy_positions[i].y) + enemy_positions[i].x) = 'G';
			else
				*(*(*mystruct->map + enemy_positions[i].y) + enemy_positions[i].x) = 'C';
			// draw changes
			mlx_put_image_to_window(mystruct->vars->mlx, mystruct->vars->win, (mystruct->all_images.images + 4)->img,
				(enemy_previous_positions + i)->x * CELL_SIZE_W, (enemy_previous_positions + i)->y * CELL_SIZE_W);
		}
		// draw exit again
		*(*(*mystruct->map + exit.y) + exit.x) = 'E';
		mlx_put_image_to_window(mystruct->vars->mlx, mystruct->vars->win, (mystruct->all_images.images + 2)->img, exit.x * CELL_SIZE_W, exit.y * CELL_SIZE_H);
		for (int i = 0; i < number_of_enemies; i++) // draw new position of all
			mlx_put_image_to_window(mystruct->vars->mlx, mystruct->vars->win, (mystruct->all_images.images + 3)->img,
				(enemy_positions + i)->x * CELL_SIZE_W, (enemy_positions + i)->y * CELL_SIZE_W);
		// print_map(mystruct);
		// printf("\n\n");
	}
	for (int i = 0; i < number_of_enemies; i++) // check for collision at every moment
	{
		if (*(*(*mystruct->map + enemy_positions[i].y) + enemy_positions[i].x) == 'G' ||
			*(*(*mystruct->map + enemy_positions[i].y) + enemy_positions[i].x) == 'P')
		{
			free(enemy_positions);
			free(enemy_previous_positions);
			number_of_calls = 0;
			number_of_enemies = 0;
			reset_map(mystruct);
			return (0);
		}
	}
	number_of_calls++;
	if (number_of_calls == 10000)
		number_of_calls = 1;
	return (0);
}
