/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils7.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 19:14:35 by edavid            #+#    #+#             */
/*   Updated: 2021/07/16 19:20:52 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"
#include "mlx/mlx.h"

int	pow_int(int base, int exp)
{
	if (exp < 0)
		exp *= -1;
	if (base == 0)
		return (0);
	if (exp == 0)
		return (1);
	return (base * pow_int(base, exp - 1));
}

void	draw_map_helper(t_mystruct *mystruct, int cur_map_height,
int cur_character, int cur_cell)
{
	t_point	img_offset;

	img_offset.x = CELL_SIZE_W * cur_character;
	img_offset.y = CELL_SIZE_H * cur_map_height;
	mlx_put_image_to_window(mystruct->vars->mlx, mystruct->vars->win,
		(mystruct->all_images.images + 4)->img,
		img_offset.x, img_offset.y);
	if (cur_cell == '1')
		mlx_put_image_to_window(mystruct->vars->mlx, mystruct->vars->win,
			(mystruct->all_images.images)->img, img_offset.x, img_offset.y);
	else if (cur_cell == '0')
		mlx_put_image_to_window(mystruct->vars->mlx, mystruct->vars->win,
			(mystruct->all_images.images + 1)->img, img_offset.x, img_offset.y);
	else if (cur_cell == 'E')
		mlx_put_image_to_window(mystruct->vars->mlx, mystruct->vars->win,
			(mystruct->all_images.images + 2)->img, img_offset.x, img_offset.y);
	else if (cur_cell == 'P')
	{
		mystruct->cur_position->x = cur_character;
		mystruct->cur_position->y = cur_map_height;
		mlx_put_image_to_window(mystruct->vars->mlx, mystruct->vars->win,
			(mystruct->all_images.playerMovement)->img, img_offset.x,
			img_offset.y);
	}
}
