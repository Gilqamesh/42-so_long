/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_ninja.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 17:26:19 by edavid            #+#    #+#             */
/*   Updated: 2021/07/16 17:40:41 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "ft_move_ninja.h"
#include "mlx_linux/mlx.h"
#include "ft_utils.h"
#include "ft_hooks.h"

static void	exit_program_cleanly(t_mystruct *mystruct)
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

static void	move_ninja2(t_mystruct *mystruct, char *cur_c, char *prev_c,
int *is_all_collected)
{
	*cur_c = *(*(*mystruct->map + mystruct->cur_position->y)
			+ mystruct->cur_position->x);
	*prev_c = *(*(*mystruct->map + *mystruct->prev_y) + *mystruct->prev_x);
	mlx_put_image_to_window(mystruct->vars->mlx, mystruct->vars->win,
		(mystruct->all_images.images + 4)->img, *mystruct->prev_x * CELL_SIZE_W,
		*mystruct->prev_y * CELL_SIZE_H);
	if (*prev_c == 'Q')
		mlx_put_image_to_window(mystruct->vars->mlx, mystruct->vars->win,
			(mystruct->all_images.images + 2)->img, *mystruct->prev_x
			* CELL_SIZE_W, *mystruct->prev_y * CELL_SIZE_H);
	if (*cur_c == 'C')
	{
		mlx_put_image_to_window(mystruct->vars->mlx, mystruct->vars->win,
			(mystruct->all_images.images + 4)->img, mystruct->cur_position->x
			* CELL_SIZE_W, mystruct->cur_position->y * CELL_SIZE_H);
		*(*((*mystruct->map) + *mystruct->prev_y) + *mystruct->prev_x) = '0';
		*(*((*mystruct->map) + mystruct->cur_position->y)
				+ mystruct->cur_position->x) = 'P';
	}
	if (IS_BONUS)
		*is_all_collected = 1;
	else
		*is_all_collected = all_collected(mystruct->map, mystruct->map_width,
				mystruct->map_height);
}

static void	move_ninja3(t_mystruct *mystruct, int *movement_state,
char *cur_c, char *prev_c)
{
	if (IS_BONUS)
		number_put(*mystruct->move_counter, (t_point){600, 600}, mystruct,
			*mystruct->move_counter - 1);
	else
		printf("move counter: %d\n", *mystruct->move_counter);
	if (++(*movement_state) == 8)
		*movement_state = 0;
	mlx_put_image_to_window(mystruct->vars->mlx, mystruct->vars->win,
		(mystruct->all_images.playerMovement + *movement_state)->img,
		mystruct->cur_position->x * CELL_SIZE_W,
		mystruct->cur_position->y * CELL_SIZE_H);
	if (*prev_c == 'Q')
		*(*((*mystruct->map) + *mystruct->prev_y)
				+ *mystruct->prev_x) = 'E';
	else
		*(*((*mystruct->map) + *mystruct->prev_y)
				+ *mystruct->prev_x) = '0';
	if (*cur_c == 'E')
		*(*((*mystruct->map) + mystruct->cur_position->y)
				+ mystruct->cur_position->x) = 'Q';
	else
		*(*((*mystruct->map) + mystruct->cur_position->y)
				+ mystruct->cur_position->x) = 'P';
}

int	move_ninja(int keycode, t_mystruct *mystruct)
{
	char		cur_c;
	char		prev_c;
	int			is_all_collected;
	static int	movement_state;

	if (keycode == 53)
		exit_program_cleanly(mystruct);
	if (wasd_pressed(keycode, mystruct))
	{
		move_ninja2(mystruct, &cur_c, &prev_c, &is_all_collected);
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
			move_ninja3(mystruct, &movement_state, &cur_c, &prev_c);
	}
	return (0);
}
