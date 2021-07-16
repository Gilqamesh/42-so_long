/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 15:45:12 by edavid            #+#    #+#             */
/*   Updated: 2021/07/16 16:22:36 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_utils2.h"
#include "ft_structs.h"
#include "mlx/mlx.h"

static int	wasd_pressed_helper(int keycode, t_mystruct *mystruct)
{
	if (keycode == 13)
	{
		if (*mystruct->prev_y - 1 < 0 || *(*(*mystruct->map + *mystruct->prev_y
					- 1) + *mystruct->prev_x) == '1')
			return (0);
		mystruct->cur_position->y--;
	}
	else if (keycode == 0)
	{
		if (*mystruct->prev_x - 1 < 0 || *(*(*mystruct->map
					+ *mystruct->prev_y) + *mystruct->prev_x - 1) == '1')
			return (0);
		mystruct->cur_position->x--;
	}
	else if (keycode == 1)
	{
		if (*mystruct->prev_y + 1 > mystruct->map_height
			|| *(*(*mystruct->map + *mystruct->prev_y + 1)
				+ *mystruct->prev_x) == '1')
			return (0);
		mystruct->cur_position->y++;
	}
	(*mystruct->move_counter)++;
	return (1);
}

int	wasd_pressed(int keycode, t_mystruct *mystruct)
{
	if (keycode == 13 || !keycode || keycode == 1 || keycode == 2)
	{
		*mystruct->prev_x = mystruct->cur_position->x;
		*mystruct->prev_y = mystruct->cur_position->y;
		if (keycode == 13 || !keycode || keycode == 1)
			return (wasd_pressed_helper(keycode, mystruct));
		else if (keycode == 2)
		{
			if (*mystruct->prev_x + 1 > mystruct->map_width
				|| *(*(*mystruct->map + *mystruct->prev_y) + *mystruct->prev_x
					+ 1) == '1')
				return (0);
			mystruct->cur_position->x++;
		}
		(*mystruct->move_counter)++;
		return (1);
	}
	return (0);
}

int	all_collected(char ***map, int width, int height)
{
	int	y;
	int	x;

	x = -1;
	y = -1;
	while (++y < height)
		while (++x < width)
			if (*(*(*map + y) + x) == 'C')
				return (0);
	return (1);
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

int	count_collectibles(t_mystruct *mystruct)
{
	int	counter;
	int	y;
	int	x;

	counter = 0;
	y = -1;
	x = -1;
	while (++y < mystruct->map_height)
		while (++x < mystruct->map_width)
			if (*(*(*mystruct->map + y) + x) == 'C')
				counter++;
	return (counter);
}
