/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 10:02:09 by edavid            #+#    #+#             */
/*   Updated: 2021/07/12 20:53:05 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "mlx/mlx.h"
#include "ft_hooks.h"
#include "ft_colors.h"
#include "ft_basic_shapes.h"

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

static int	wasd_pressed2(int keycode, int *x, int *y, int *prev_x, int *prev_y, int map_width, int map_height, char ***map)
{
	 for (int i = 0; i < map_height; i++)	// PRINT OUT PARSED MAP
	 	printf("%s\n", *(*map + i));
	if (keycode == 13) // W
	{
		*prev_x = *x;
		*prev_y = *y;
		if (*prev_y - 1 < 0)
			return (0);
		if (*(*(*map + *prev_y - 1) + *prev_x) == '1')
			return (0);
		(*y)--;
		return (1);
	}
	else if (keycode == 0) // A
	{
		*prev_x = *x;
		*prev_y = *y;
		if (*prev_x - 1 < 0)
			return (0);
		if (*(*(*map + *prev_y) + *prev_x - 1) == '1')
			return (0);
		(*x)--;
		return (1);
	}
	else if (keycode == 1) // S
	{
		*prev_x = *x;
		*prev_y = *y;
		if (*prev_y + 1 > map_height)
			return (0);
		if (*(*(*map + *prev_y + 1) + *prev_x) == '1')
			return (0);
		(*y)++;
		return (1);
	}
	else if (keycode == 2) // D
	{
		*prev_x = *x;
		*prev_y = *y;
		if (*prev_x + 1 > map_width)
			return (0);
		if (*(*(*map + *prev_y) + *prev_x + 1) == '1')
			return (0);
		(*x)++;
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

int		move_ninja(int keycode, t_mystruct2 *mystruct)
{
	int	cur_line_counter;

	if (keycode == 53)
	{
		mlx_destroy_window(mystruct->vars->mlx, mystruct->vars->win);
		cur_line_counter = 0;
		while (cur_line_counter < mystruct->map_height)
			free(*(*mystruct->map + cur_line_counter++));
		free(*mystruct->map);
		exit(EXIT_SUCCESS);
	}
	if (wasd_pressed2(keycode, mystruct->x, mystruct->y, mystruct->prev_x, mystruct->prev_y, mystruct->map_width, mystruct->map_height, mystruct->map))
	{
		// EMPTY SPACE IMAGE[1] DOES NOT REPLACE PREVIOUS IMAGE CORRECTLY
		mlx_put_image_to_window(mystruct->vars->mlx, mystruct->vars->win, mystruct->images[1].img, *mystruct->prev_x * CELL_SIZE_W, *mystruct->prev_y * CELL_SIZE_H);
		mlx_put_image_to_window(mystruct->vars->mlx, mystruct->vars->win, mystruct->images[3].img, *mystruct->x * CELL_SIZE_W, *mystruct->y * CELL_SIZE_H);
	}
	return (0);
}
