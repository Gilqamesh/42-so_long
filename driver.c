/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   driver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 16:16:58 by edavid            #+#    #+#             */
/*   Updated: 2021/07/10 14:53:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include "mlx_linux/mlx.h"
#include "ft_utils.h"
#include "ft_basic_shapes.h"
#include "ft_colors.h"
#include "ft_hooks.h"
#include "ft_testers.h"
#include "ft_structs.h"
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 500

int main(void)
{
	t_vars	vars;

	// initialize MiniLibX, store the location of the MLX instance in mlx var
	vars.mlx = mlx_init();
	// create a window with specified dimensions and title, and store the location in mlx_win var
	vars.win = mlx_new_window(vars.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World!");

	//t_data	img;

	// initialize image
	//img.img = mlx_new_image(vars.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	// call mlx_get_data_addr to set some of the vars of t_data
	//img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	// line_put_parametric(&img, 50, 50, 200, 200, mlx_red.value, 1000);
	// register hook functions
	//mlx_key_hook(vars.win, key_hook, &vars);
	// mlx_mouse_hook(vars.win, mouse_hook, &vars);

	/* testing drawing functions */

	// testing loop hook, calls the function (2nd param) with the parameter (3rd param)
	// int			x = 100;
	// int			y = 100;
	// int			prev_x = x;
	// int			prev_y = y;
	// t_mystruct	mystruct = {&vars, &img, &x, &y, &prev_x, &prev_y};
	// // mlx_hook(vars.win, 2, (1L<<2), move_circle, &mystruct);
	// gradient_opposite(&mystruct);
	
	// reading image
	// t_data	sprite_img;
	// int		img_width;
	// int		img_height;
	// sprite_img.img = mlx_xpm_file_to_image(vars.mlx, "redhood.xpm", &img_width, &img_height);
	// if (!sprite_img.img)
	// {
	// 	printf("Could not open image\n");
	// 	return (-1);
	// }
	// sprite_img.addr = mlx_get_data_addr(sprite_img.img, &sprite_img.bits_per_pixel, &sprite_img.line_length, &sprite_img.endian);
	// resize image
	// for (int i = 0; i < img_width; i++)
	// {
	// 	for (int j = 0; j < img_height; j++)
	// 	{
	// 		int	pos = j * sprite_img.line_length + i * (sprite_img.bits_per_pixel / 8);
	// 		int	pos_half = j / 2 * sprite_img.line_length + i / 2 * (sprite_img.bits_per_pixel / 8);
	// 		*(unsigned int *)(sprite_img.addr + pos_half) = *(unsigned int *)(sprite_img.addr + pos);
	// 	}
	// }
	// *(sprite_img.addr + 50) = '\0';


	// pushes image to the window
	//mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	//mlx_put_image_to_window(vars.mlx, vars.win, sprite_img.img, 0, 0);
	// sprite_img = mlx_xpm_file_to_image(vars.mlx, "cursor.xpm", &img_width, &img_height);
	// if (!sprite_img)
	// {
	// 	printf("Could not open image\n");
	// 	return (-1);
	// }
	// mlx_put_image_to_window(vars.mlx, vars.win, sprite_img, 0, 0);

	// to initiate the window rendering, each hook that was registered prior to this will be called accordingly by order of registration
	//mlx_loop(vars.mlx);
}
