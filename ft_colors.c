/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 16:17:06 by edavid            #+#    #+#             */
/*   Updated: 2021/07/09 14:31:58 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_colors.h"
#include "ft_utils.h"

t_node	mlx_red = {0x00FF0000, "red", 0};
t_node	mlx_purple = {0x00FF00FF, "purple", 0};
t_node	mlx_blue = {0x000000FF, "blue", 0};
t_node	mlx_cyan = {0x0000FFFF, "cyan", 0};
t_node	mlx_green = {0x0000FF00, "green", 0};
t_node	mlx_yellow = {0x00FFFF00, "yellow", 0};
t_node	mlx_white = {0x00FFFFFF, "white", 0};
t_node	mlx_black = {0x00000000, "black", 0};

void	init_rainbow(void)
{
	mlx_red.next = &mlx_purple;
	mlx_purple.next = &mlx_blue;
	mlx_blue.next = &mlx_cyan;
	mlx_cyan.next = &mlx_green;
	mlx_green.next = &mlx_yellow;
	mlx_yellow.next = &mlx_red;
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

t_rgba	make_rgba(int red, int green, int blue, int alpha)
{
	return ((t_rgba){alpha, red, green, blue});
}

t_hsl	rgba_to_hsl(t_rgba rgba)
{
	double	red;
	double	green;
	double	blue;
	double	Cmax;
	double	Cmin;
	int		hue;
	double	saturation;
	double	lightness;

	red = rgba.red / 255.0;
	green = rgba.green / 255.0;
	blue = rgba.blue / 255.0;
	Cmax = max_of_3(red, green, blue);
	Cmin = min_of_3(red, green, blue);
	if (!(Cmax - Cmin))
		hue = 0;
	else if (Cmax == red)
		hue = 60 * ((int)((green - blue) / (Cmax - Cmin)) % 6);
	else if (Cmax == green)
		hue = 60 * ((blue - red) / (Cmax - Cmin) + 2);
	else
		hue = 60 * ((red - green) / (Cmax - Cmin) + 4);
	lightness = (Cmax + Cmin) / 2;
	if (!(Cmax - Cmin))
		saturation = 0;
	else
		saturation = (Cmax - Cmin) / (1 - abs_double(2 * lightness - 1));
	return ((t_hsl){hue, (char)(saturation * 100), (char)(lightness * 100)});
}

t_rgba	hsl_to_rgba(t_hsl hsl)
{
	double	C;
	double	X;
	double	m;
	double	red;
	double	green;
	double	blue;

	C = (1 - abs_double(2 * hsl.lightness / 100.0 - 1)) * hsl.saturation / 100.0;
	X = C * (1 - abs_double((int)(hsl.hue / 60.0) % 2 - 1));
	m = hsl.lightness / 100.0 - C / 2;
	if (hsl.hue < 60)
	{
		red = C;
		green = X;
		blue = 0;
	}
	else if (hsl.hue < 120)
	{
		red = X;
		green = C;
		blue = 0;
	}
	else if (hsl.hue < 180)
	{
		red = 0;
		green = C;
		blue = X;
	}
	else if (hsl.hue < 240)
	{
		red = 0;
		green = X;
		blue = C;
	}
	else if (hsl.hue < 300)
	{
		red = X;
		green = 0;
		blue = C;
	}
	else
	{
		red = C;
		green = 0;
		blue = X;
	}
	return ((t_rgba){0, (red + m) * 255, (green + m) * 255, (blue + m) * 255});
}

int		shade_add(double shade, int color)
{
	t_hsl	hsl;

	if (shade < 0)
		shade = 0;
	if (shade > 1)
		shade = 1;
	hsl = rgba_to_hsl(hex_to_rgba(color));
	hsl.lightness *= 1 - shade;
	return (rgba_to_hex(hsl_to_rgba(hsl)));
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

int		opposite_color_get(int hex)
{
	t_rgba	rgb;

	rgb = hex_to_rgba(hex);
	rgb.alpha = 255 - rgb.alpha;
	rgb.red = 255 - rgb.red;
	rgb.green = 255 - rgb.green;
	rgb.blue = 255 - rgb.blue;
	return (rgba_to_hex(rgb));
}
