/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_image_initialize.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 11:50:05 by edavid            #+#    #+#             */
/*   Updated: 2021/07/16 19:38:32 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "mlx_linux/mlx.h"
#include "ft_image_initialize.h"
#include "ft_utils.h"
#include "ft_structs.h"

static void	extract_image(t_data *images, struct s_args1 args1)
{
	t_point	parameters;

	images->img = mlx_xpm_file_to_image(args1.vars->mlx, args1.filePath,
			&parameters.x, &parameters.y);
	images->addr = mlx_get_data_addr(images->img, &images->bits_per_pixel,
			&images->line_length, &images->endian);
	get_part_of_img(*args1.vars, images, args1.A, args1.B);
	resize_img(*args1.vars, images, (t_point){args1.B.x - args1.A.x,
		args1.A.y - args1.B.y}, args1.cell_size);
}

static void	init_images(t_mystruct *mystruct)
{
	mystruct->all_images.img->img = mlx_new_image(mystruct->vars->mlx,
			SCREEN_WIDTH, SCREEN_HEIGHT);
	mystruct->all_images.img->addr = mlx_get_data_addr(
			mystruct->all_images.img->img,
			&mystruct->all_images.img->bits_per_pixel,
			&mystruct->all_images.img->line_length,
			&mystruct->all_images.img->endian);
	extract_image(mystruct->all_images.images, (struct s_args1){
		(t_point){255, 865}, (t_point){287, 833}, "sprites/megapixelart.xpm",
		mystruct->vars, (t_point){CELL_SIZE_W, CELL_SIZE_H}});
	extract_image(mystruct->all_images.images + 1, (struct s_args1){
		(t_point){0, 765}, (t_point){33, 730}, "sprites/megapixelart.xpm",
		mystruct->vars, (t_point){CELL_SIZE_W, CELL_SIZE_H}});
	extract_image(mystruct->all_images.images + 2, (struct s_args1){
		(t_point){353, 1025}, (t_point){386, 990}, "sprites/megapixelart.xpm",
		mystruct->vars, (t_point){CELL_SIZE_W, CELL_SIZE_H}});
	extract_image(mystruct->all_images.images + 3, (struct s_args1){
		(t_point){100, 520}, (t_point){133, 483}, "sprites/megapixelart.xpm",
		mystruct->vars, (t_point){CELL_SIZE_W, CELL_SIZE_H}});
	*(mystruct->all_images.images + 4) = get_blank_image(mystruct->vars->mlx,
			CELL_SIZE_W, CELL_SIZE_H);
}

void	initialize_images(t_mystruct *mystruct)
{
	int		i;

	init_images(mystruct);
	i = -1;
	while (++i < 8)
		extract_image(mystruct->all_images.playerMovement + i, (struct s_args1){
			(t_point){73 + i * 180, 116}, (t_point){113 + i * 180, 58},
			"sprites/run.xpm", mystruct->vars, (t_point){CELL_SIZE_W,
			CELL_SIZE_H}});
	extract_image(mystruct->all_images.numberImages, (struct s_args1){
		(t_point){355, 732}, (t_point){465, 555}, "sprites/numbers.xpm",
		mystruct->vars, (t_point){50, 82}});
	i = -1;
	while (++i < 8)
		extract_image(mystruct->all_images.numberImages + i + 1,
			(struct s_args1){(t_point){15 + 145 * (i % 4),
			71 + 177 + 240 * (i / 4)}, (t_point){15 + 140 + 145 * (i % 4),
			71 + 240 * (i / 4)}, "sprites/numbers.xpm", mystruct->vars,
			(t_point){50, 82}});
	extract_image(mystruct->all_images.numberImages + 9, (struct s_args1){
		(t_point){124, 732}, (t_point){232, 555}, "sprites/numbers.xpm",
		mystruct->vars, (t_point){50, 82}});
	*(mystruct->all_images.numberImages + 10) = get_blank_image(
			mystruct->vars->mlx, 50, 82);
}
