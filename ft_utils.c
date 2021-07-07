/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 15:39:04 by edavid            #+#    #+#             */
/*   Updated: 2021/07/07 19:41:05 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"
#include <limits.h>

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

t_rgba	hex_to_rgba(int hex)
{
	return ((t_rgba){(hex & 0xFF000000) >> 24, (hex & 0x00FF0000) >> 16,
					(hex & 0x0000FF00) >> 8, hex & 0x000000FF});
}

int		rgba_to_hex(t_rgba rgba)
{
	return (rgba.alpha << 24 | rgba.red << 16 | rgba.green << 8 | rgba.blue);
}

int		get_red_from_hex(int hex)
{
	return ((hex & 0x00FF0000) >> 16);
}

int		get_green_from_hex(int hex)
{
	return ((hex & 0x0000FF00) >> 8);
}

int		get_blue_from_hex(int hex)
{
	return (hex & 0x000000FF);
}

t_rgba	make_rgba(int red, int green, int blue, int alpha)
{
	return ((t_rgba){alpha << 24, red << 16, green << 8, blue});
}

double	abs_double(double a)
{
	if (a > 0)
		return (a);
	return (-a);
}
