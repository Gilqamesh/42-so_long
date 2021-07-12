/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   driver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 16:16:58 by edavid            #+#    #+#             */
/*   Updated: 2021/07/12 19:08:11 by edavid           ###   ########.fr       */
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
#include <unistd.h>
#include "gnl/ft_get_next_line.h"
#include <fcntl.h>
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define CELL_SIZE_W 50
#define CELL_SIZE_H 50

int main(void)
{
	// read in files
	int		fd;
	char	*line;
	char	**map;
	int		line_counter;

	fd = open("maps/simple.ber", O_RDONLY);
	if (fd == -1)
		return (-1);
	// parse map
	line_counter = 0;
	get_next_line(fd, &line);
	while (*line != '\0')
	{
		map = ft_realloc(map, ++line_counter * sizeof(char *));
		*(map + line_counter - 1) = line;
		get_next_line(fd, &line);
	}
	free(line);
		// for (int i = 0; i < line_counter; i++)	// PRINT OUT PARSED MAP
		// 	printf("%s\n", *(map + i));
	//

	close(fd);
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
	//

	// INITIALIZE MAP ON SCREEN
	int		cur_line_counter;
	int		cur_character;
	char	cur_cell;

	cur_line_counter = 0;
	while (cur_line_counter < line_counter)
	{
		cur_character = 0;
		cur_cell = *(*(map + cur_line_counter) + cur_character);
		while (cur_cell != '\0')
		{
			if (cur_cell == '1') // WALL
			{
				
			}
			else if (cur_cell == '0') // EMPTY SPACE
			{

			}
			else if (cur_cell == 'E') // MAP EXIT
			{

			}
			else if (cur_cell == 'P') // PLAYER
			{
				
			}
			else if (cur_cell == ) // 
		}
	}
	//

	// to initiate the window rendering, each hook that was registered prior to this will be called accordingly by order of registration
	mlx_loop(vars.mlx);

	return (0);
}
