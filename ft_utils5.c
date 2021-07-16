/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 18:52:29 by edavid            #+#    #+#             */
/*   Updated: 2021/07/16 19:40:11 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"
#include "mlx_linux/mlx.h"
#include "libft/libft.h"
#include <stdio.h>

double	min_of_3(double a, double b, double c)
{
	if (a > b)
	{
		if (a > c)
		{
			if (b > c)
				return (c);
			else
				return (b);
		}
		else
			return (b);
	}
	else
	{
		if (b > c)
		{
			if (a > c)
				return (c);
			else
				return (a);
		}
		else
			return (a);
	}
}

void	resize_img(t_vars vars, t_data *img, t_point old_params,
t_point new_params)
{
	t_data	new_img;
	double	ratio_w;
	double	ratio_h;
	int		y;
	int		x;

	ratio_w = (double)new_params.x / old_params.x;
	ratio_h = (double)new_params.y / old_params.y;
	new_img.img = mlx_new_image(vars.mlx, new_params.x, new_params.y);
	new_img.addr = mlx_get_data_addr(new_img.img, &new_img.bits_per_pixel,
			&new_img.line_length, &new_img.endian);
	y = -1;
	while (++y < old_params.y)
	{
		x = -1;
		while (++x < old_params.x)
			my_mlx_pixel_put(&new_img, x * ratio_w, y * ratio_h,
				*(int *)(img->addr + y * img->line_length + x
					* (img->bits_per_pixel / 8)));
	}
	mlx_destroy_image(vars.mlx, img->img);
	*img = new_img;
}

void	get_part_of_img(t_vars vars, t_data *img, t_point bot_left,
t_point top_right)
{
	t_data	new_img;
	t_point	A;
	t_point	B;

	new_img.img = mlx_new_image(vars.mlx, abs_int(top_right.x - bot_left.x),
			abs_int(bot_left.y - top_right.y));
	new_img.addr = mlx_get_data_addr(new_img.img, &new_img.bits_per_pixel,
			&new_img.line_length, &new_img.endian);
	B.x = top_right.y;
	B.y = 0;
	while (++B.x < bot_left.y)
	{
		A.x = bot_left.x;
		A.y = 0;
		while (++A.x < top_right.x)
		{
			my_mlx_pixel_put(&new_img, A.y, B.y, *(int *)(img->addr + B.x
					* img->line_length + A.x * (img->bits_per_pixel / 8)));
			A.y++;
		}
		B.y++;
	}
	mlx_destroy_image(vars.mlx, img->img);
	*img = new_img;
}

void	*ft_realloc(void *src, size_t size)
{
	void	*new;

	new = malloc(size);
	if (!new)
		return (src);
	if (!src)
		return (new);
	ft_memmove(new, src, size);
	free(src);
	return (new);
}

void	free_map(char ***map, int n_of_pointers)
{
	while (n_of_pointers--)
		free(*(*map + n_of_pointers));
	free(*map);
	*map = 0;
}
