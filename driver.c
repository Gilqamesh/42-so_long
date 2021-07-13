/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   driver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 16:16:58 by edavid            #+#    #+#             */
/*   Updated: 2021/07/13 11:53:13 by edavid           ###   ########.fr       */
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
#include "ft_error.h"
#include "errno.h"
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

int main(void)
{
	// read in files
	int		fd;
	char	*line;
	char	**map;
	int		line_counter;
	int		map_width;

	fd = open("maps/simple.ber", O_RDONLY);
	if (fd == -1)
		ft_error("open returned -1 fd");
	// parse map
	line_counter = 0;
	if (get_next_line(fd, &line) < 0)
		ft_error("get_next_line negative return value");
	map_width = ft_strlen(line) - 2;
	while (*line != '\0')
	{
		map = ft_realloc(map, ++line_counter * sizeof(char *));
		*(map + line_counter - 1) = line;
		if (get_next_line(fd, &line) < 0)
		{
			free_map(&map, line_counter);
			ft_error("get_next_line negative return value");
		}
		if (*line && (int)ft_strlen(line) - 2 != map_width)
		{
			free_map(&map, line_counter);
			ft_error("map is not rectangular");
		}
	}
	free(line);
	validate_map(&map, line_counter, map_width + 2);
		
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
	t_data	playerImgBlank;
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
	// PLAYER IMAGE BLANK
		playerImgBlank.img = mlx_new_image(vars.mlx, playerImgWidth, playerImgHeight);
		playerImgBlank.addr = mlx_get_data_addr(playerImgBlank.img, &playerImgBlank.bits_per_pixel, &playerImgBlank.line_length, &playerImgBlank.endian);
		get_part_of_img(vars, &playerImgBlank, A_point_player, B_point_player);
		resize_img(vars, &playerImgBlank, B_point_player.x - A_point_player.x, A_point_player.y - B_point_player.y, CELL_SIZE_W, CELL_SIZE_H);
		for (int y = 0; y < CELL_SIZE_H; y++)
			for (int x = 0; x < CELL_SIZE_W; x++)
				my_mlx_pixel_put(&playerImgBlank, x, y, mlx_black.value);
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
	images[5] = playerImgBlank;
	//

	// INITIALIZE MAP ON SCREEN
	int		start_x;
	int		start_y;
	int		cur_line_counter;
	int		cur_character;
	char	cur_cell;
	t_point	img_offset;

	cur_line_counter = 0;
	while (cur_line_counter < line_counter)
	{
		cur_character = 0;
		cur_cell = *(*(map + cur_line_counter) + cur_character);
		while (cur_cell != '\0')
		{
			img_offset.x = CELL_SIZE_W * cur_character;
			img_offset.y = CELL_SIZE_H * cur_line_counter;
			if (cur_cell == '1') // WALL
				mlx_put_image_to_window(vars.mlx, vars.win, wallImg.img, img_offset.x, img_offset.y);
			else if (cur_cell == '0') // EMPTY SPACE
				mlx_put_image_to_window(vars.mlx, vars.win, emptySpaceImg.img, img_offset.x, img_offset.y);
			else if (cur_cell == 'E') // MAP EXIT
				mlx_put_image_to_window(vars.mlx, vars.win, mapExitImg.img, img_offset.x, img_offset.y);
			else if (cur_cell == 'P') // PLAYER
			{
				start_x = cur_character;
				start_y = cur_line_counter;
				mlx_put_image_to_window(vars.mlx, vars.win, playerImg.img, img_offset.x, img_offset.y);
			}
			else if (cur_cell == 'C') // COLLECTIBLE 
				mlx_put_image_to_window(vars.mlx, vars.win, collectibleImg.img, img_offset.x, img_offset.y);
			cur_cell = *(*(map + cur_line_counter) + ++cur_character);
		}
		cur_line_counter++;
	}
	//
	// HOOKS
	int	prev_x;
	int	prev_y;
	t_mystruct2	mystruct = {
		&vars,
		images,
		&start_x,
		&start_y,
		&prev_x,
		&prev_y,
		map_width,
		line_counter - 2,
		&map
	};
	mlx_hook(vars.win, 17, (1L<<17), exit_clicked, &mystruct);
	mlx_hook(vars.win, 02, (1L<<0), move_ninja, &mystruct);
	//

	// to initiate the window rendering, each hook that was registered prior to this will be called accordingly by order of registration
	mlx_loop(vars.mlx);

	return (0);
}
