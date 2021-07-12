/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 10:02:09 by edavid            #+#    #+#             */
/*   Updated: 2021/07/12 14:45:17 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "mlx/mlx.h"
#include "ft_hooks.h"
#include "ft_colors.h"
#include "ft_basic_shapes.h"

int	key_hook(int keycode, t_vars *vars)
{
	(void)vars;
	printf("keycode: %d\n", keycode);
	if (keycode == 53)
		mlx_destroy_window(vars->mlx, vars->win);
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
