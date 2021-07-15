/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   driver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 16:16:58 by edavid            #+#    #+#             */
/*   Updated: 2021/07/15 16:14:31 by edavid           ###   ########.fr       */
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

static void	initialize_images(t_mystruct *mystruct)
{
	t_point	A;
	t_point	B;
	t_point parameters;

	mystruct->all_images->img->img = mlx_new_image(mystruct->vars->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	mystruct->all_images->img->addr = mlx_get_data_addr(mystruct->all_images->img->img,
		&mystruct->all_images->img->bits_per_pixel, &mystruct->all_images->img->line_length,
		&mystruct->all_images->img->endian);

	// WALL IMAGE
		(*mystruct->all_images->images)->img = mlx_xpm_file_to_image(mystruct->vars->mlx, "sprites/megapixelart.xpm", &parameters.x, &parameters.y);
		(*mystruct->all_images->images)->addr = mlx_get_data_addr((*mystruct->all_images->images)->img, &(*mystruct->all_images->images)->bits_per_pixel,
			&(*mystruct->all_images->images)->line_length, &(*mystruct->all_images->images)->endian);
		A = (t_point){255, 865};
		B = (t_point){287, 833};
		get_part_of_img(*mystruct->vars, *mystruct->all_images->images, A, B);
		resize_img(*mystruct->vars, *mystruct->all_images->images, (t_point){B.x - A.x, A.y - B.y}, (t_point){CELL_SIZE_W, CELL_SIZE_H});
	//
	// EMPTY IMAGE
		(*mystruct->all_images->images + 1)->img = mlx_xpm_file_to_image(mystruct->vars->mlx, "sprites/megapixelart.xpm", &parameters.x, &parameters.y);
		(*mystruct->all_images->images + 1)->addr = mlx_get_data_addr((*mystruct->all_images->images + 1)->img, &(*mystruct->all_images->images + 1)->bits_per_pixel,
			&(*mystruct->all_images->images + 1)->line_length, &(*mystruct->all_images->images + 1)->endian);
		A = (t_point){0, 765};
		B = (t_point){33, 730};
		get_part_of_img(*mystruct->vars, *mystruct->all_images->images + 1, A, B);
		resize_img(*mystruct->vars, *mystruct->all_images->images + 1, (t_point){B.x - A.x, A.y - B.y}, (t_point){CELL_SIZE_W, CELL_SIZE_H});
	//
	// MAP EXIT IMAGE
		(*mystruct->all_images->images + 2)->img = mlx_xpm_file_to_image(mystruct->vars->mlx, "sprites/megapixelart.xpm", &parameters.x, &parameters.y);
		(*mystruct->all_images->images + 2)->addr = mlx_get_data_addr((*mystruct->all_images->images + 2)->img, &(*mystruct->all_images->images + 2)->bits_per_pixel,
			&(*mystruct->all_images->images + 2)->line_length, &(*mystruct->all_images->images + 2)->endian);
		A = (t_point){353, 1025};
		B = (t_point){386, 990};
		get_part_of_img(*mystruct->vars, *mystruct->all_images->images + 2, A, B);
		resize_img(*mystruct->vars, *mystruct->all_images->images + 2, (t_point){B.x - A.x, A.y - B.y}, (t_point){CELL_SIZE_W, CELL_SIZE_H});
	//
	// COLLECTIBLE IMG
		(*mystruct->all_images->images + 3)->img = mlx_xpm_file_to_image(mystruct->vars->mlx, "sprites/megapixelart.xpm", &parameters.x, &parameters.y);
		(*mystruct->all_images->images + 3)->addr = mlx_get_data_addr((*mystruct->all_images->images + 3)->img, &(*mystruct->all_images->images + 3)->bits_per_pixel,
			&(*mystruct->all_images->images + 3)->line_length, &(*mystruct->all_images->images + 3)->endian);
		A = (t_point){100, 520};
		B = (t_point){133, 483};
		get_part_of_img(*mystruct->vars, *mystruct->all_images->images + 3, A, B);
		resize_img(*mystruct->vars, *mystruct->all_images->images + 3, (t_point){B.x - A.x, A.y - B.y}, (t_point){CELL_SIZE_W, CELL_SIZE_H});
	//
	// EMPTY SPACE IMG
		*(*mystruct->all_images->images + 4) = get_blank_image(mystruct->vars->mlx, CELL_SIZE_W, CELL_SIZE_H);
	//

	// PLAYER IMAGE
		for (int i = 0; i < 8; i++)
		{
			(*mystruct->all_images->playerMovement + i)->img = mlx_xpm_file_to_image(mystruct->vars->mlx, "sprites/run.xpm", &parameters.x, &parameters.y);
			(*mystruct->all_images->playerMovement + i)->addr = mlx_get_data_addr((*mystruct->all_images->playerMovement + i)->img, &(*mystruct->all_images->playerMovement + i)->bits_per_pixel,
				&(*mystruct->all_images->playerMovement + i)->line_length, &(*mystruct->all_images->playerMovement + i)->endian);
			A = (t_point){73 + i * 180, 116};
			B = (t_point){113 + i * 180, 58};
			get_part_of_img(*mystruct->vars, *mystruct->all_images->playerMovement + i, A, B);
			resize_img(*mystruct->vars, *mystruct->all_images->playerMovement + i, (t_point){B.x - A.x, A.y - B.y}, (t_point){CELL_SIZE_W, CELL_SIZE_H});
			// mlx_put_image_to_window(vars.mlx, vars.win, (playerMovement + i)->img, 10 + i * 80, 10);
		}
	//
	//

	// get number images
	int		numberIndex;
	(*mystruct->all_images->numberImages)->img = mlx_xpm_file_to_image(mystruct->vars->mlx, "sprites/numbers.xpm", &parameters.x, &parameters.y);
	(*mystruct->all_images->numberImages)->addr = mlx_get_data_addr((*mystruct->all_images->numberImages)->img, &(*mystruct->all_images->numberImages)->bits_per_pixel,
		&(*mystruct->all_images->numberImages)->line_length, &(*mystruct->all_images->numberImages)->endian);
	A = (t_point){355, 732};
	B = (t_point){465, 555};
	get_part_of_img(*mystruct->vars, *mystruct->all_images->numberImages, A, B);
	resize_img(*mystruct->vars, *mystruct->all_images->numberImages, (t_point){A.x - B.x, B.y - A.y}, (t_point){50, 82});
	for (int rows = 0; rows < 2; rows++)
	{
		for (int cols = 0; cols < 4; cols++)
		{
			numberIndex = rows * 4 + cols + 1;
			(*mystruct->all_images->numberImages + numberIndex)->img = mlx_xpm_file_to_image(mystruct->vars->mlx, "sprites/numbers.xpm", &parameters.x, &parameters.y);
			(*mystruct->all_images->numberImages + numberIndex)->addr = mlx_get_data_addr((*mystruct->all_images->numberImages + numberIndex)->img, &(*mystruct->all_images->numberImages + numberIndex)->bits_per_pixel,
				&(*mystruct->all_images->numberImages + numberIndex)->line_length, &(*mystruct->all_images->numberImages + numberIndex)->endian);
			A = (t_point){15 + 145 * cols, 71 + 177 + 240 * rows};
			B = (t_point){15 + 140 + 145 * cols, 71 + 240 * rows};
			get_part_of_img(*mystruct->vars, *mystruct->all_images->numberImages + numberIndex, A, B);
			resize_img(*mystruct->vars, *mystruct->all_images->numberImages + numberIndex, (t_point){A.x - B.x, B.y - A.y}, (t_point){50, 82});
			if (rows == 1 && cols == 3 )
				break ;
		}
	}
	(*mystruct->all_images->numberImages + 9)->img = mlx_xpm_file_to_image(mystruct->vars->mlx, "sprites/numbers.xpm", &parameters.x, &parameters.y);
	(*mystruct->all_images->numberImages + 9)->addr = mlx_get_data_addr((*mystruct->all_images->numberImages + 9)->img, &(*mystruct->all_images->numberImages + 9)->bits_per_pixel,
		&(*mystruct->all_images->numberImages + 9)->line_length, &(*mystruct->all_images->numberImages + 9)->endian);
	A = (t_point){124, 732};
	B = (t_point){232, 555};
	get_part_of_img(*mystruct->vars, *mystruct->all_images->numberImages + 9, A, B);
	resize_img(*mystruct->vars, *mystruct->all_images->numberImages + 9, (t_point){A.x - B.x, B.y - A.y}, (t_point){50, 82});
	*(*mystruct->all_images->numberImages + 10) = get_blank_image(mystruct->vars->mlx, 50, 82);
	//

}

int main(int argc, char **argv)
{
	char		**map;
	int			map_height;
	int			map_width;
	t_mystruct	mystruct;
	t_point 	start_point;
	int			prev_x;
	int			prev_y;
	int			move_counter;
	int			need_reset;
	t_images	all_images;
	t_data		img;
	t_data		*images;
	t_data		*numberImages;
	t_data		*playerMovement;
	t_vars		vars;

	if (argc != 2)
		ft_error("usage: a.out filepath");
	initialize_map(&map, &map_width, &map_height, argv[1]);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "so_long");
	images = malloc(6 * sizeof(*images));
	numberImages = malloc(11 * sizeof(*numberImages));
	playerMovement = malloc(8 * sizeof(*playerMovement));
	all_images = (t_images){
		&img,
		&images,
		&numberImages,
		&playerMovement
	};
	move_counter = 0;
	need_reset = 0;
	mystruct = (t_mystruct){
		&vars,
		&all_images,
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
	initialize_images(&mystruct);
	draw_map(&mystruct);
	#ifdef BONUS
	number_put(0, (t_point){600, 600}, &mystruct, 0);
	#endif
	mlx_hook(vars.win, 17, (1L<<17), exit_clicked, &mystruct);
	mlx_hook(vars.win, 02, (1L<<0), move_ninja, &mystruct);
	#ifdef BONUS
	mlx_loop_hook(vars.mlx, patrol_enemy, &mystruct);
	#endif
	mlx_loop(vars.mlx);
	return (0);
}
