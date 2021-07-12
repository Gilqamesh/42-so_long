/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 15:39:04 by edavid            #+#    #+#             */
/*   Updated: 2021/07/12 18:38:27 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "ft_utils.h"
#include "mlx/mlx.h"

void	my_mlx_pixel_put(t_data *data, double x, double y, int color)
{
	char	*dst;
	int		a;
	int		b;

	a = round_to_nearest(x);
	b = round_to_nearest(y);
	dst = data->addr + (b * data->line_length + a * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int		round_to_nearest(double a)
{
	if ((int)(a * 10) % 10 < 5)
		return ((int)a);
	return ((int)(a + 1));
}

int		abs_int(int a)
{
	if (a > 0)
		return (a);
	if (a == INT_MIN)
		return (INT_MAX);
	return (-a);
}

double	abs_double(double a)
{
	if (a > 0)
		return (a);
	return (-a);
}

double	max_of_3(double a, double b, double c)
{
	if (a > b)
	{
		if (a > c)
			return (a);
		else // b > c not possible, because a > b > c and c > a is a contradiction
			return (c);
	}
	else // b > a
	{
		if (b > c)
			return (b);
		else // a > c not possible, because b > a > c and c > b is a contradiction
			return (c);
	}
}

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

void	resize_img(t_vars vars, t_data *img, int old_width, int old_height, int new_width, int new_height)
{
	t_data	new_img;
	double	ratio_w;
	double	ratio_h;

	ratio_w = (double)new_width / old_width;
	ratio_h = (double)new_height / old_height;
	new_img.img = mlx_new_image(vars.mlx, new_width, new_height);
	new_img.addr = mlx_get_data_addr(new_img.img, &new_img.bits_per_pixel, &new_img.line_length, &new_img.endian);
	for (int y = 0; y < old_height; y++)
		for (int x = 0; x < old_width; x++)
			my_mlx_pixel_put(&new_img, x * ratio_w, y * ratio_h, *(int *)(img->addr + y * img->line_length + x * (img->bits_per_pixel / 8)));
	mlx_destroy_image(vars.mlx, img->img);
	*img = new_img;
}

void	get_part_of_img(t_vars vars, t_data *img, t_point bot_left, t_point top_right)
{
	t_data	new_img;
	new_img.img = mlx_new_image(vars.mlx, abs_int(top_right.x - bot_left.x), abs_int(bot_left.y - top_right.y));
	new_img.addr = mlx_get_data_addr(new_img.img, &new_img.bits_per_pixel, &new_img.line_length, &new_img.endian);
	for (int y = top_right.y, y_new = 0; y < bot_left.y; y++, y_new++)
		for (int x = bot_left.x, x_new = 0; x < top_right.x; x++, x_new++)
			my_mlx_pixel_put(&new_img, x_new, y_new, *(int *)(img->addr + y * img->line_length + x * (img->bits_per_pixel / 8)));
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
