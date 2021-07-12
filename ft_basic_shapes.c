/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_basic_shapes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 15:33:48 by edavid            #+#    #+#             */
/*   Updated: 2021/07/12 16:38:11 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "ft_basic_shapes.h"
#include "ft_colors.h"
#include "ft_utils.h"
#define PI 3.142

// the distribution of pixels is not even so its not easy to manipulate them, but the logic is pretty fast, does not iterate over unnecessary pixels
void	circle_put_quick(t_data *data, int a, int b, int radius)
{
	int			x;

	// (x - a)^2 + (y - b)^2 = R^2
	// y = +-sqrt(R^2 - (x - a)^2) + b
	// x = +-sqrt(R^2 - (y - b)^2) + a
	x = a - radius;
	while (x <= a + radius)
	{
		my_mlx_pixel_put(data, x, sqrt(radius * radius - (x - a) * (x - a)) + b, mlx_white.value);
		my_mlx_pixel_put(data, x, -sqrt(radius * radius - (x - a) * (x - a)) + b, mlx_white.value);
		x++;
	}
	x = b - radius;
	while (x <= b + radius)
	{
		my_mlx_pixel_put(data, sqrt(radius * radius - (x - b) * (x - b)) + a, x, mlx_white.value);
		my_mlx_pixel_put(data, -sqrt(radius * radius - (x - b) * (x - b)) + a, x, mlx_white.value);
		x++;
	}
}

// uses the parametric equation of a circle, pixels are distributed evenly
void	circle_put_parametric(t_data *data, int a, int b, int radius, int color_hex)
{
	double	t;
	t_node	*color;
	int		pixels;

	// x = a + Rcos(t)
	// y = b + Rsin(t)
	t = 2 * PI * 1000;
	init_rainbow();
	if (color_hex == -1)
		color = &mlx_red;
	else
	{
		color = malloc(sizeof(*color));
		color->value = color_hex;
	}
	pixels = 0;
	while (t >= 0)
	{
		my_mlx_pixel_put(data, a + radius * cos(t / 1000), b + radius * sin(t / 1000), color_hex == -1 ? color->value : color_hex);
		if (color_hex == -1 && ++pixels % 100 == 0)
			color = color->next;
		t--;
	}
	if (color_hex != -1)
		free(color);
}

// uses parametric equation of line segment
void	line_put_parametric(t_data *data, int x1, int y1, int x2, int y2, int color, int iter_n)
{
	double	t;
	double	increment;

	// x = t * x1 + (1 - t)x2
	// y = t * y1 + (1 - t)y2
	t = 0;
	increment = (double)1 / iter_n;
	while (t <= 1)
	{
		my_mlx_pixel_put(data, t * x1 + (1 - t) * x2, t * y1 + (1 - t) * y2, color);
		t += increment;
	}
}

void	square_put(t_data *data, t_point bot_left, t_point top_right, int color, int iter_n, void (*line_fn)(t_data *data, int x1, int y1, int x2, int y2, int color, int iter_n))
{
	(*line_fn)(data, bot_left.x, bot_left.y, top_right.x, bot_left.y, color, iter_n);
	(*line_fn)(data, top_right.x, bot_left.y, top_right.x, top_right.y, color, iter_n);
	(*line_fn)(data, top_right.x, top_right.y, bot_left.x, top_right.y, color, iter_n);
	(*line_fn)(data, bot_left.x, top_right.y, bot_left.x, bot_left.y, color, iter_n);
}

void	triangle_put(t_data *data, t_point A, t_point B, t_point C, int color, int iter_n, void (*line_fn)(t_data *data, int x1, int y1, int x2, int y2, int color, int iter_n))
{
	(*line_fn)(data, A.x, A.y, B.x, B.y, color, iter_n);
	(*line_fn)(data, B.x, B.y, C.x, C.y, color, iter_n);
	(*line_fn)(data, C.x, C.y, A.x, A.y, color, iter_n);
}

void	line_put_gradient(t_data *data, t_point A, t_point B, int color1, int color2, int iter_n)
{
	double	t;
	double	increment;
	t_rgba	cur_rgba;
	double	cur_red;
	double	cur_green;
	double	cur_blue;
	double	red_inc;
	double	green_inc;
	double	blue_inc;

	t = 0;
	increment = (double)1 / iter_n;
	cur_red = get_red_from_hex(color1);
	cur_green = get_green_from_hex(color1);
	cur_blue = get_blue_from_hex(color1);
	red_inc = (get_red_from_hex(color2) - get_red_from_hex(color1)) / (double)iter_n;
	green_inc = (get_green_from_hex(color2) - get_green_from_hex(color1)) / (double)iter_n;
	blue_inc = (get_blue_from_hex(color2) - get_blue_from_hex(color1)) / (double)iter_n;
	cur_rgba = hex_to_rgba(color1);
	while (t <= 1)
	{
		my_mlx_pixel_put(data, t * B.x + (1 - t) * A.x, t * B.y + (1 - t) * A.y, rgba_to_hex(cur_rgba));
		cur_red += red_inc;
		cur_green += green_inc;
		cur_blue += blue_inc;
		cur_rgba = make_rgba(round_to_nearest(cur_red), round_to_nearest(cur_green),
					round_to_nearest(cur_blue), 0);
		t += increment;
	}
}
