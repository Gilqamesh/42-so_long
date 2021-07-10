/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_testers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 13:44:53 by edavid            #+#    #+#             */
/*   Updated: 2021/07/10 14:26:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "mlx_linux/mlx.h"
#include "ft_testers.h"
#include "ft_colors.h"
#include "ft_basic_shapes.h"
#include "ft_hooks.h"
#include "ft_structs.h"

int		gradient_opposite(t_mystruct *mystruct)
{
	for (int i = 0; i < 500; i++)
		line_put_parametric(mystruct->img, 50 + i + *mystruct->x, 50, 1000 + i + *mystruct->x, 1000, mlx_black.value, 1000);
	(*mystruct->x)++;
	for (int i = 0; i < 500; i++)
		line_put_gradient(mystruct->img, (t_point){50 + i + *mystruct->x, 50}, (t_point){1000 + i + *mystruct->x, 1000}, mlx_red.value, opposite_color_get(mlx_red.value), 1000);
	mlx_put_image_to_window(mystruct->vars->mlx, mystruct->vars->win, mystruct->img->img, 0, 0);
	return (0);
}

int		shader(t_data *img)
{
	for (int i = 0; i < 1000; i++)
	{
		if (i < 500)
			line_put_parametric(img, 50 + i, 50, 600 + i, 1000, shade_add(0 + i / 600.0, mlx_red.value), 1000);
		else
			line_put_parametric(img, 50 + i, 50, 600 + i, 1000, shade_add(0 + (1000 - i) / 600.0, mlx_red.value), 1000);
	}
	return (0);
}

int		color_changer(t_mystruct *mystruct)
{
	line_put_parametric(mystruct->img, *mystruct->x, 10, *mystruct->x, 1000, mlx_red.value, 1000);
	mlx_put_image_to_window(mystruct->vars->mlx, mystruct->vars->win, mystruct->img->img, 0, 0);
	(*mystruct->x)++;
	return (0);
}
