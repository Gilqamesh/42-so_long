/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   driver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 16:16:58 by edavid            #+#    #+#             */
/*   Updated: 2021/07/15 14:49:53 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "mlx/mlx.h"
#include "ft_utils.h"
#include "ft_colors.h"
#include "ft_hooks.h"
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
	t_data	blankImg;
	// WALL IMAGE
		int	wallImgWidth, wallImgHeight;
		wallImg.img = mlx_xpm_file_to_image(vars.mlx, "sprites/megapixelart.xpm", &wallImgWidth, &wallImgHeight);
		wallImg.addr = mlx_get_data_addr(wallImg.img, &wallImg.bits_per_pixel, &wallImg.line_length, &wallImg.endian);
		t_point	A_point_wall = {255, 865}, B_point_wall = {287, 833};
		get_part_of_img(vars, &wallImg, A_point_wall, B_point_wall);
		resize_img(vars, &wallImg, (t_point){B_point_wall.x - A_point_wall.x, A_point_wall.y - B_point_wall.y}, (t_point){CELL_SIZE_W, CELL_SIZE_H});
	//
	// BLANK IMAGE
		blankImg = get_blank_image(vars.mlx, CELL_SIZE_W, CELL_SIZE_H);
	//
	// MAP EXIT IMAGE
		int	mapExitImgWidth, mapExitImgHeight;
		mapExitImg.img = mlx_xpm_file_to_image(vars.mlx, "sprites/megapixelart.xpm", &mapExitImgWidth, &mapExitImgHeight);
		mapExitImg.addr = mlx_get_data_addr(mapExitImg.img, &mapExitImg.bits_per_pixel, &mapExitImg.line_length, &mapExitImg.endian);
		t_point A_point_map = {353, 1025}, B_point_map = {386, 990};
		get_part_of_img(vars, &mapExitImg, A_point_map, B_point_map);
		resize_img(vars, &mapExitImg, (t_point){B_point_map.x - A_point_map.x, A_point_map.y - B_point_map.y}, (t_point){CELL_SIZE_W, CELL_SIZE_H});
	//
	// COLLECTIBLE IMG
		int	collectibleImgWidth, collectibleImgHeight;
		collectibleImg.img = mlx_xpm_file_to_image(vars.mlx, "sprites/megapixelart.xpm", &collectibleImgWidth, &collectibleImgHeight);
		collectibleImg.addr = mlx_get_data_addr(collectibleImg.img, &collectibleImg.bits_per_pixel, &collectibleImg.line_length, &collectibleImg.endian);
		t_point A_point_collectible = {100, 520}, B_point_collectible = {133, 483};
		get_part_of_img(vars, &collectibleImg, A_point_collectible, B_point_collectible);
		resize_img(vars, &collectibleImg, (t_point){B_point_collectible.x - A_point_collectible.x, A_point_collectible.y - B_point_collectible.y}, (t_point){CELL_SIZE_W, CELL_SIZE_H});
	//
	// EMPTY IMAGE
		int	emptyImgWidth, emptyImgHeight;
		emptySpaceImg.img = mlx_xpm_file_to_image(vars.mlx, "sprites/megapixelart.xpm", &emptyImgWidth, &emptyImgHeight);
		emptySpaceImg.addr = mlx_get_data_addr(emptySpaceImg.img, &emptySpaceImg.bits_per_pixel, &emptySpaceImg.line_length, &emptySpaceImg.endian);
		t_point A_point_empty = {0, 765}, B_point_empty = {33, 730};
		get_part_of_img(vars, &emptySpaceImg, A_point_empty, B_point_empty);
		resize_img(vars, &emptySpaceImg, (t_point){B_point_empty.x - A_point_empty.x, A_point_empty.y - B_point_empty.y}, (t_point){CELL_SIZE_W, CELL_SIZE_H});
	//
	t_data	*images = malloc(6 * sizeof(*images));
	images[0] = wallImg;
	images[1] = emptySpaceImg;
	images[2] = mapExitImg;
	images[3] = collectibleImg;
	images[4] = blankImg;
	// PLAYER IMAGE
		t_data	*playerMovement = malloc(8 * sizeof(*playerMovement));
		for (int i = 0; i < 8; i++)
		{
			int	playerImgWidth, playerImgHeight;
			playerMovement[i].img = mlx_xpm_file_to_image(vars.mlx, "sprites/run.xpm", &playerImgWidth, &playerImgHeight);
			playerMovement[i].addr = mlx_get_data_addr(playerMovement[i].img, &(playerMovement + i)->bits_per_pixel, &(playerMovement + i)->line_length, &(playerMovement + i)->endian);
			t_point A_point_player = {73 + i * 180, 116}, B_point_player = {113 + i * 180, 58};
			get_part_of_img(vars, playerMovement + i, A_point_player, B_point_player);
			resize_img(vars, playerMovement + i, (t_point){B_point_player.x - A_point_player.x, A_point_player.y - B_point_player.y}, (t_point){CELL_SIZE_W, CELL_SIZE_H});
			// mlx_put_image_to_window(vars.mlx, vars.win, (playerMovement + i)->img, 10 + i * 80, 10);
		}
	//
	//

	// get number images
	t_data	*numberImages = malloc(11 * sizeof(*numberImages));
	int		numberWidth;
	int		numberHeight;
	int		numberIndex;
	numberImages[0].img = mlx_xpm_file_to_image(vars.mlx, "sprites/numbers.xpm", &numberWidth, &numberHeight);
	numberImages[0].addr = mlx_get_data_addr(numberImages[0].img, &numberImages[0].bits_per_pixel, &numberImages[0].line_length, &numberImages[0].endian);
	t_point Q_0 = {355, 732};
	t_point P_0 = {465, 555};
	get_part_of_img(vars, &numberImages[0], Q_0, P_0);
	resize_img(vars, numberImages, (t_point){P_0.x - Q_0.x, Q_0.y - P_0.y}, (t_point){50, 82});
	for (int rows = 0; rows < 2; rows++)
	{
		for (int cols = 0; cols < 4; cols++)
		{
			numberIndex = rows * 4 + cols + 1;
			numberImages[numberIndex].img = mlx_xpm_file_to_image(vars.mlx, "sprites/numbers.xpm", &numberWidth, &numberHeight);
			numberImages[numberIndex].addr = mlx_get_data_addr(numberImages[numberIndex].img, &numberImages[numberIndex].bits_per_pixel, &numberImages[numberIndex].line_length, &numberImages[numberIndex].endian);
			int x_offset = 15;
			int y_offset = 71;
			t_point Q = {x_offset + 145 * cols, y_offset + 177 + 240 * rows};
			t_point P = {x_offset + 140 + 145 * cols, y_offset + 240 * rows};
			get_part_of_img(vars, numberImages + numberIndex, Q, P);
			resize_img(vars, numberImages + numberIndex, (t_point){P.x - Q.x, Q.y - P.y}, (t_point){50, 82});
			if (rows == 1 && cols == 3 )
				break ;
		}
	}
	numberImages[9].img = mlx_xpm_file_to_image(vars.mlx, "sprites/numbers.xpm", &numberWidth, &numberHeight);
	numberImages[9].addr = mlx_get_data_addr(numberImages[9].img, &numberImages[9].bits_per_pixel, &numberImages[9].line_length, &numberImages[9].endian);
	t_point Q = {124, 732};
	t_point P = {232, 555};
	get_part_of_img(vars, &numberImages[9], Q, P);
	resize_img(vars, numberImages + 9, (t_point){P.x - Q.x, Q.y - P.y}, (t_point){50, 82});
	numberImages[10] = get_blank_image(vars.mlx, 50, 82);
	//

	
	t_point start_point;
	int	prev_x;
	int	prev_y;
	int	move_counter = 0;
	int	need_reset = 0;
	t_mystruct2	mystruct = {
		&vars,
		images,
		numberImages,
		playerMovement,
		&start_point,
		&prev_x,
		&prev_y,
		map_width,
		map_height,
		&map,
		argv[1],
		&move_counter,
		&need_reset
	};

	// draw map on screen
	draw_map(&mystruct);
	//

	#ifdef BONUS
	number_put(0, (t_point){600, 600}, &mystruct, 0);
	#endif
	// HOOKS
	mlx_hook(vars.win, 17, (1L<<17), exit_clicked, &mystruct);
	mlx_hook(vars.win, 02, (1L<<0), move_ninja, &mystruct);
	#ifdef BONUS
	mlx_loop_hook(vars.mlx, patrol_enemy, &mystruct);
	#endif
	//

	// to initiate the window rendering, each hook that was registered prior to this will be called accordingly by order of registration
	mlx_loop(vars.mlx);

	return (0);
}
