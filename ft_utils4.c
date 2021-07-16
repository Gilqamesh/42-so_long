/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 18:51:07 by edavid            #+#    #+#             */
/*   Updated: 2021/07/16 19:23:57 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"
#include <limits.h>

int	round_to_nearest(double a)
{
	if ((int)(a * 10) % 10 < 5)
		return ((int)a);
	return ((int)(a + 1));
}

int	abs_int(int a)
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
		else
			return (c);
	}
	else
	{
		if (b > c)
			return (b);
		else
			return (c);
	}
}

void	my_mlx_pixel_put(t_data *data, double x, double y, int color)
{
	char	*dst;
	int		a;
	int		b;

	a = round_to_nearest(x);
	b = round_to_nearest(y);
	dst = data->addr + (b * data->line_length + a * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
