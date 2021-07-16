/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   driver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 16:16:58 by edavid            #+#    #+#             */
/*   Updated: 2021/07/16 17:35:09 by edavid           ###   ########.fr       */
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
#include "ft_image_initialize.h"

static void	init_struct(t_mystruct *mystruct)
{
	t_data		*img;
	t_data		*images;
	t_data		*numberImages;
	t_data		*playerMovement;

	img = malloc(sizeof(*img));
	img->img = mlx_new_image(mystruct->vars->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	images = malloc(6 * sizeof(*images));
	numberImages = malloc(11 * sizeof(*numberImages));
	playerMovement = malloc(8 * sizeof(*playerMovement));
	mystruct->all_images.img = img;
	mystruct->all_images.images = images;
	mystruct->all_images.numberImages = numberImages;
	mystruct->all_images.playerMovement = playerMovement;
}

static void	init_struct2(t_mystruct *mystruct)
{
	t_vars		*vars;
	int			*move_counter;
	int			*need_reset;

	vars = malloc(sizeof(*vars));
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, SCREEN_WIDTH, SCREEN_HEIGHT,
			"so_long");
	move_counter = malloc(sizeof(*move_counter));
	need_reset = malloc(sizeof(*need_reset));
	*move_counter = 0;
	*need_reset = 0;
	mystruct->vars = vars;
	mystruct->move_counter = move_counter;
	mystruct->need_reset = need_reset;
	mystruct->map_height = 0;
	mystruct->map_width = 0;
}

static void	init_struct3(t_mystruct *mystruct)
{
	t_point		*cur_position;
	int			*prev_x;
	char		***map;
	int			*prev_y;

	cur_position = malloc(sizeof(*cur_position));
	mystruct->cur_position = cur_position;
	prev_x = malloc(sizeof(*prev_x));
	prev_y = malloc(sizeof(*prev_y));
	mystruct->prev_x = prev_x;
	mystruct->prev_y = prev_y;
	map = malloc(sizeof(*map));
	mystruct->map = map;
}

static void	initialize_struct(t_mystruct *mystruct)
{
	init_struct3(mystruct);
	init_struct2(mystruct);
	init_struct(mystruct);
}

int	main(int argc, char **argv)
{
	t_mystruct	mystruct;

	if (argc != 2)
		ft_error("usage: a.out filepath");
	mystruct.filePath = argv[1];
	initialize_struct(&mystruct);
	initialize_map(&mystruct);
	initialize_images(&mystruct);
	draw_map(&mystruct);
	if (IS_BONUS)
		number_put(0, (t_point){600, 600}, &mystruct, 0);
	mlx_hook(mystruct.vars->win, 17, (1L << 17), exit_clicked, &mystruct);
	mlx_hook(mystruct.vars->win, 02, (1L << 0), move_ninja, &mystruct);
	if (IS_BONUS)
		mlx_loop_hook(mystruct.vars->mlx, patrol_enemy, &mystruct);
	mlx_loop(mystruct.vars->mlx);
	return (0);
}
