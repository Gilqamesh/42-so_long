/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   driver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 16:16:58 by edavid            #+#    #+#             */
/*   Updated: 2021/07/12 17:25:45 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include "mlx/mlx.h"
#include "ft_utils.h"
#include "ft_basic_shapes.h"
#include "ft_colors.h"
#include "ft_hooks.h"
#include "ft_testers.h"
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define CELL_SIZE_W 50
#define CELL_SIZE_H 50

int main(void)
{
	t_vars	vars;

	// initialize MiniLibX, store the location of the MLX instance in mlx var
	vars.mlx = mlx_init();
	// create a window with specified dimensions and title, and store the location in mlx_win var
	vars.win = mlx_new_window(vars.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "so long");

	t_data	img;
	// initialize image
	img.img = mlx_new_image(vars.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	// call mlx_get_data_addr to set some of the vars of t_data
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	// get images for Empty space, Wall, Collectible, Map exit and PlayerImg
	//t_data	emptySpaceImg;
	//t_data	wallImg;
	t_data	collectibleImg;
	//t_data	mapExitImg;
	//t_data	playerImg;

	// WALL IMAGE
		// int	wallImgWidth, wallImgHeight;
		// wallImg.img = mlx_xpm_file_to_image(vars.mlx, "sprites/megapixelart.xpm", &wallImgWidth, &wallImgHeight);
		// wallImg.addr = mlx_get_data_addr(wallImg.img, &wallImg.bits_per_pixel, &wallImg.line_length, &wallImg.endian);
		// get_part_of_img(vars, &wallImg, (t_point){255, 865}, (t_point){287, 833});
		// resize_img(vars, &wallImg, 32, 32, CELL_SIZE_W, CELL_SIZE_H);
		// mlx_put_image_to_window(vars.mlx, vars.win, wallImg.img, 0, 0);
	//

	// PLAYER IMAGE
		// int	playerImgWidth, playerImgHeight;
		// playerImg.img = mlx_xpm_file_to_image(vars.mlx, "sprites/run.xpm", &playerImgWidth, &playerImgHeight);
		// playerImg.addr = mlx_get_data_addr(playerImg.img, &playerImg.bits_per_pixel, &playerImg.line_length, &playerImg.endian);
		// t_point A_point = {73, 116}, B_point = {113, 58};
		// get_part_of_img(vars, &playerImg, A_point, B_point);
		// resize_img(vars, &playerImg, B_point.x - A_point.x, A_point.y - B_point.y, CELL_SIZE_W, CELL_SIZE_H);
		// mlx_put_image_to_window(vars.mlx, vars.win, playerImg.img, A_point.x, B_point.y);
	//

	// MAP EXIT IMAGE
		// int	mapExitImgWidth, mapExitImgHeight;
		// mapExitImg.img = mlx_xpm_file_to_image(vars.mlx, "sprites/megapixelart.xpm", &mapExitImgWidth, &mapExitImgHeight);
		// mapExitImg.addr = mlx_get_data_addr(mapExitImg.img, &mapExitImg.bits_per_pixel, &mapExitImg.line_length, &mapExitImg.endian);
		// t_point A_point_map = {353, 1025}, B_point_map = {386, 990};
		// get_part_of_img(vars, &mapExitImg, A_point_map, B_point_map);
		// resize_img(vars, &mapExitImg, B_point_map.x - A_point_map.x, A_point_map.y - B_point_map.y, CELL_SIZE_W, CELL_SIZE_H);
		// mlx_put_image_to_window(vars.mlx, vars.win, mapExitImg.img, 0, 0);
	//

	// COLLECTIBLE IMG
		int	collectibleImgWidth, collectibleImgHeight;
		collectibleImg.img = mlx_xpm_file_to_image(vars.mlx, "sprites/megapixelart.xpm", &collectibleImgWidth, &collectibleImgHeight);
		collectibleImg.addr = mlx_get_data_addr(collectibleImg.img, &collectibleImg.bits_per_pixel, &collectibleImg.line_length, &collectibleImg.endian);
		t_point A_point_collectible = {0, 765}, B_point_collectible = {33, 730};
		get_part_of_img(vars, &collectibleImg, A_point_collectible, B_point_collectible);
		resize_img(vars, &collectibleImg, B_point_collectible.x - A_point_collectible.x, A_point_collectible.y - B_point_collectible.y, CELL_SIZE_W, CELL_SIZE_H);
		mlx_put_image_to_window(vars.mlx, vars.win, collectibleImg.img, 0, 0);
	//

	// EMPTY IMAGE
	//
		// int	emptyImgWidth, emptyImgHeight;
		// emptySpaceImg.img = mlx_xpm_file_to_image(vars.mlx, "sprites/megapixelart.xpm", &emptyImgWidth, &emptyImgHeight);
		// emptySpaceImg.addr = mlx_get_data_addr(emptySpaceImg.img, &emptySpaceImg.bits_per_pixel, &emptySpaceImg.line_length, &emptySpaceImg.endian);
		// t_point A_point_collectible = {0, 765}, B_point_collectible = {33, 730};
		// get_part_of_img(vars, &emptySpaceImg, A_point_collectible, B_point_collectible);
		// resize_img(vars, &emptySpaceImg, B_point_collectible.x - A_point_collectible.x, A_point_collectible.y - B_point_collectible.y, CELL_SIZE_W, CELL_SIZE_H);
		// mlx_put_image_to_window(vars.mlx, vars.win, emptySpaceImg.img, 0, 0);
	//

	// to initiate the window rendering, each hook that was registered prior to this will be called accordingly by order of registration
	mlx_loop(vars.mlx);

	return (0);
}
