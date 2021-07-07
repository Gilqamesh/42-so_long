/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 15:37:24 by edavid            #+#    #+#             */
/*   Updated: 2021/07/07 19:41:22 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_H
# define FT_UTILS_H

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_rgba
{
	int	alpha;
	int	red;
	int	green;
	int	blue;
}				t_rgba;

void	my_mlx_pixel_put(t_data *data, double x, double y, int color);
int		round_to_nearest(double a);
int		abs_int(int a);
t_rgba	hex_to_rgba(int hex);
int		rgba_to_hex(t_rgba rgba);
int		get_red_from_hex(int hex);
int		get_green_from_hex(int hex);
int		get_blue_from_hex(int hex);
t_rgba	make_rgba(int red, int green, int blue, int alpha);
double	abs_double(double a);

#endif
