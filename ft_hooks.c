/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 10:02:09 by edavid            #+#    #+#             */
/*   Updated: 2021/07/16 15:59:07 by edavid           ###   ########.fr       */
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
#include "ft_utils2.h"
#include "ft_utils3.h"

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
	if (wasd_pressed(keycode, mystruct))
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
		if (cur_c == 'E' && is_all_collected)
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
	if (i != 5)
	{
		*previous_position = *current_position;
		str = cur_node->name;
		if (!ft_strncmp(str, "up_char", 2))
			current_position->y -= 1;
		else if (!ft_strncmp(str, "left_char", 2))
			current_position->x -= 1;
		else if (!ft_strncmp(str, "down_char", 2))
			current_position->y += 1;
		else
			current_position->x += 1;
	}
}

int	patrol_enemy(t_mystruct *mystruct)
{
	static t_point	exit;
	static t_point	*enemy_positions;
	static t_point	*enemy_previous_positions;
	static int		number_of_enemies;
	static int		number_of_calls;

	if (*mystruct->need_reset || !number_of_calls)
		initialize_vars(&enemy_positions, &enemy_previous_positions, &number_of_enemies, &exit, mystruct);
	if (number_of_calls == 9999)
	{
		for (int i = 0; i < number_of_enemies; i++)
		{
			get_next_position(mystruct, enemy_positions + i, enemy_previous_positions + i);
			*(*(*mystruct->map + enemy_previous_positions[i].y) + enemy_previous_positions[i].x) = '0';
			if (*(*(*mystruct->map + enemy_positions[i].y) + enemy_positions[i].x) == 'P')
				*(*(*mystruct->map + enemy_positions[i].y) + enemy_positions[i].x) = 'G';
			else
				*(*(*mystruct->map + enemy_positions[i].y) + enemy_positions[i].x) = 'C';
			mlx_put_image_to_window(mystruct->vars->mlx, mystruct->vars->win, (mystruct->all_images.images + 4)->img,
				(enemy_previous_positions + i)->x * CELL_SIZE_W, (enemy_previous_positions + i)->y * CELL_SIZE_W);
		}
		*(*(*mystruct->map + exit.y) + exit.x) = 'E';
		mlx_put_image_to_window(mystruct->vars->mlx, mystruct->vars->win, (mystruct->all_images.images + 2)->img, exit.x * CELL_SIZE_W, exit.y * CELL_SIZE_H);
		for (int i = 0; i < number_of_enemies; i++)
			mlx_put_image_to_window(mystruct->vars->mlx, mystruct->vars->win, (mystruct->all_images.images + 3)->img,
				(enemy_positions + i)->x * CELL_SIZE_W, (enemy_positions + i)->y * CELL_SIZE_W);
	}
	for (int i = 0; i < number_of_enemies; i++)
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
