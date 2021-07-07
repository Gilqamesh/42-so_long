/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   driver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 16:16:58 by edavid            #+#    #+#             */
/*   Updated: 2021/07/07 19:47:50 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "mlx/mlx.h"
#include "ft_utils.h"
#include "ft_basic_shapes.h"
#include "ft_colors.h"
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

int main(void)
{
	void	*mlx;
	void	*mlx_win;

	// initialize MiniLibX, store the location of the MLX instance in mlx var
	mlx = mlx_init();
	// create a window with specified dimensions and title, and store the location in mlx_win var
	mlx_win = mlx_new_window(mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World!");

	t_data	img;

	// initialize image
	img.img = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	// call mlx_get_data_addr to set some of the vars of t_data
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	// circle_put_parametric(&img, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 100);
	// line_put_parametric(&img, 10, 10, 100, 10, mlx_red.value, 1000);
	// square_put(&img, 800, 800, 1000, 1000, mlx_cyan.value, 1000, line_put_parametric);
	// triangle_put(&img, (t_point){80, 200}, (t_point){90, 400}, (t_point){200, 300}, mlx_green.value, 200, line_put_parametric);
	line_put_gradient(&img, (t_point){50, 50}, (t_point){1200, 500}, mlx_blue.value, mlx_red.value, 1000);
	
	// pushes image to the window
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);

	// to initiate the window rendering
	mlx_loop(mlx);
}
