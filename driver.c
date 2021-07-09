/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   driver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 16:16:58 by edavid            #+#    #+#             */
/*   Updated: 2021/07/09 10:59:27 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include "mlx/mlx.h"
#include "ft_utils.h"
#include "ft_basic_shapes.h"
#include "ft_colors.h"
#include "ft_hooks.h"
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

int main(void)
{
	t_vars	vars;

	// initialize MiniLibX, store the location of the MLX instance in mlx var
	vars.mlx = mlx_init();
	// create a window with specified dimensions and title, and store the location in mlx_win var
	vars.win = mlx_new_window(vars.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World!");

	t_data	img;

	// initialize image
	img.img = mlx_new_image(vars.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	// call mlx_get_data_addr to set some of the vars of t_data
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	line_put_parametric(&img, 50, 50, 200, 200, mlx_red.value, 1000);
	// register hook function with mlx_key_hook
	//mlx_key_hook(vars.win, key_hook, &vars);
	//mlx_mouse_hook(vars.win, mouse_hook, &vars);
	mlx_hook(vars.win, 6, 0L, mouse_hook, &vars);

	/* testing drawing functions */
	// for (int i = 0; i < 1000; i++)
	// {
	// 	if (i < 500)
	// 		line_put_parametric(&img, 50 + i, 50, 600 + i, 1000, shade_add(0 + i / 600.0, mlx_red.value), 1000);
	// 	else
	// 		line_put_parametric(&img, 50 + i, 50, 600 + i, 1000, shade_add(0 + (1000 - i) / 600.0, mlx_red.value), 1000);
	// }
	for (int i = 0; i < 500; i++)
		line_put_gradient(&img, (t_point){50 + i, 50}, (t_point){1000 + i, 1000}, mlx_red.value, opposite_color_get(mlx_red.value), 1000);
	/* drawing */

	// pushes image to the window
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);

	// to initiate the window rendering
	mlx_loop(vars.mlx);
}
