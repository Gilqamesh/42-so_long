/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   driver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 16:16:58 by edavid            #+#    #+#             */
/*   Updated: 2021/07/13 16:45:22 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "mlx/mlx.h"
#include "ft_utils.h"
#include "ft_basic_shapes.h"
#include "ft_colors.h"
#include "ft_hooks.h"
#include "ft_testers.h"
#include "ft_error.h"
#include "errno.h"
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

int main(int argc, char **argv)
{
	// read in files
	char	**map;
	int		map_height;
	int		map_width;

	if (argc != 2)
		ft_error("usage: a.out filepath");
	initialize_map(&map, &map_width, &map_height, argv[1]);
	//
	
	// INIT SCREEN WITH MINILIBX
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
	//

	// get images for Empty space, Wall, Collectible, Map exit and PlayerImg
	t_data	emptySpaceImg;
	t_data	wallImg;
	t_data	collectibleImg;
	t_data	mapExitImg;
	t_data	playerImg;
	t_data	blankImg;
	// WALL IMAGE
		int	wallImgWidth, wallImgHeight;
		wallImg.img = mlx_xpm_file_to_image(vars.mlx, "sprites/megapixelart.xpm", &wallImgWidth, &wallImgHeight);
		wallImg.addr = mlx_get_data_addr(wallImg.img, &wallImg.bits_per_pixel, &wallImg.line_length, &wallImg.endian);
		t_point	A_point_wall = {255, 865}, B_point_wall = {287, 833};
		get_part_of_img(vars, &wallImg, A_point_wall, B_point_wall);
		resize_img(vars, &wallImg, B_point_wall.x - A_point_wall.x, A_point_wall.y - B_point_wall.y, CELL_SIZE_W, CELL_SIZE_H);
	//
	// PLAYER IMAGE
		int	playerImgWidth, playerImgHeight;
		playerImg.img = mlx_xpm_file_to_image(vars.mlx, "sprites/run.xpm", &playerImgWidth, &playerImgHeight);
		playerImg.addr = mlx_get_data_addr(playerImg.img, &playerImg.bits_per_pixel, &playerImg.line_length, &playerImg.endian);
		t_point A_point_player = {73, 116}, B_point_player = {113, 58};
		get_part_of_img(vars, &playerImg, A_point_player, B_point_player);
		resize_img(vars, &playerImg, B_point_player.x - A_point_player.x, A_point_player.y - B_point_player.y, CELL_SIZE_W, CELL_SIZE_H);
	//
	// BLANK IMAGE
		blankImg.img = mlx_new_image(vars.mlx, CELL_SIZE_W, CELL_SIZE_H);
		blankImg.addr = mlx_get_data_addr(blankImg.img, &blankImg.bits_per_pixel, &blankImg.line_length, &blankImg.endian);
		for (int y = 0; y < CELL_SIZE_H; y++)
			for (int x = 0; x < CELL_SIZE_W; x++)
				my_mlx_pixel_put(&blankImg, x, y, mlx_black.value);
	//
	// MAP EXIT IMAGE
		int	mapExitImgWidth, mapExitImgHeight;
		mapExitImg.img = mlx_xpm_file_to_image(vars.mlx, "sprites/megapixelart.xpm", &mapExitImgWidth, &mapExitImgHeight);
		mapExitImg.addr = mlx_get_data_addr(mapExitImg.img, &mapExitImg.bits_per_pixel, &mapExitImg.line_length, &mapExitImg.endian);
		t_point A_point_map = {353, 1025}, B_point_map = {386, 990};
		get_part_of_img(vars, &mapExitImg, A_point_map, B_point_map);
		resize_img(vars, &mapExitImg, B_point_map.x - A_point_map.x, A_point_map.y - B_point_map.y, CELL_SIZE_W, CELL_SIZE_H);
	//
	// COLLECTIBLE IMG
		int	collectibleImgWidth, collectibleImgHeight;
		collectibleImg.img = mlx_xpm_file_to_image(vars.mlx, "sprites/megapixelart.xpm", &collectibleImgWidth, &collectibleImgHeight);
		collectibleImg.addr = mlx_get_data_addr(collectibleImg.img, &collectibleImg.bits_per_pixel, &collectibleImg.line_length, &collectibleImg.endian);
		t_point A_point_collectible = {100, 520}, B_point_collectible = {133, 483};
		get_part_of_img(vars, &collectibleImg, A_point_collectible, B_point_collectible);
		resize_img(vars, &collectibleImg, B_point_collectible.x - A_point_collectible.x, A_point_collectible.y - B_point_collectible.y, CELL_SIZE_W, CELL_SIZE_H);
	//
	// EMPTY IMAGE
		int	emptyImgWidth, emptyImgHeight;
		emptySpaceImg.img = mlx_xpm_file_to_image(vars.mlx, "sprites/megapixelart.xpm", &emptyImgWidth, &emptyImgHeight);
		emptySpaceImg.addr = mlx_get_data_addr(emptySpaceImg.img, &emptySpaceImg.bits_per_pixel, &emptySpaceImg.line_length, &emptySpaceImg.endian);
		t_point A_point_empty = {0, 765}, B_point_empty = {33, 730};
		get_part_of_img(vars, &emptySpaceImg, A_point_empty, B_point_empty);
		resize_img(vars, &emptySpaceImg, B_point_empty.x - A_point_empty.x, A_point_empty.y - B_point_empty.y, CELL_SIZE_W, CELL_SIZE_H);
	//
	t_data	*images = malloc(6 * sizeof(*images));
	images[0] = wallImg;
	images[1] = emptySpaceImg;
	images[2] = mapExitImg;
	images[3] = playerImg;
	images[4] = collectibleImg;
	images[5] = blankImg;
	//

	// get number images
	t_data	*numberImages = malloc(9 * sizeof(*numberImages));
	int		numberWidth;
	int		numberHeight;
	// int		numberIndex;
	// for (int rows = 0; rows < 2; rows++)
	// {
	// 	for (int cols = 0; cols < 4; cols++)
	// 	{
	// 		numberIndex = rows * 4 + cols;
	// 		numberImages[numberIndex].img = mlx_xpm_file_to_image(vars.mlx, "sprites/numbers.xpm", &numberWidth, &numberHeight);
	// 		numberImages[numberIndex].addr = mlx_get_data_addr(numberImages[numberIndex].img, &numberImages[numberIndex].bits_per_pixel, &numberImages[numberIndex].line_length, &numberImages[numberIndex].endian);
	// 		t_point Q = {20 + 120 * cols, 200 + 120 * rows};
	// 		t_point P = {100 + 120 * cols, 80 + 120 * rows};
	// 		get_part_of_img(vars, numberImages + numberIndex, Q, P);
	// 		resize_img(vars, numberImages + numberIndex, numberWidth, numberHeight, CELL_SIZE_W, CELL_SIZE_H);
	// 		mlx_put_image_to_window(vars.mlx, vars.win, numberImages[numberIndex].img, cols * 50, rows * 50);
	// 		// square_put(&img, Q, P, mlx_red.value, 1000, line_put_parametric);
	// 		// mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	// 		if (rows == 1 && cols == 3 ) // dont need number 10
	// 			break ;
	// 	}
	// }
	// Width of number: 108
	// Height of number: 177
	numberImages[8].img = mlx_xpm_file_to_image(vars.mlx, "sprites/numbers.xpm", &numberWidth, &numberHeight);
	numberImages[8].addr = mlx_get_data_addr(numberImages[8].img, &numberImages[8].bits_per_pixel, &numberImages[8].line_length, &numberImages[8].endian);
	t_point Q = {124, 732};
	t_point P = {232, 555};
	get_part_of_img(vars, &numberImages[8], Q, P);
	square_put(&img, Q, P, mlx_red.value, 1000, line_put_parametric);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	resize_img(vars, &numberImages[8], numberWidth, numberHeight, CELL_SIZE_W, CELL_SIZE_H);
	mlx_put_image_to_window(vars.mlx, vars.win, numberImages[8].img, Q.x, P.y);
	//

	// draw map on screen
	// t_point start_point;
	// draw_map(&map, map_height, images, &start_point, vars);
	//
	
	// HOOKS
	// int	prev_x;
	// int	prev_y;
	// int	move_counter = 0;
	// t_mystruct2	mystruct = {
	// 	&vars,
	// 	images,
	// 	&start_point,
	// 	&prev_x,
	// 	&prev_y,
	// 	map_width,
	// 	map_height - 2,
	// 	&map,
	// 	argv[1],
	// 	&move_counter
	// };
	// mlx_hook(vars.win, 17, (1L<<17), exit_clicked, &mystruct);
	// mlx_hook(vars.win, 02, (1L<<0), move_ninja, &mystruct);
	//

	// to initiate the window rendering, each hook that was registered prior to this will be called accordingly by order of registration
	mlx_loop(vars.mlx);

	return (0);
}
