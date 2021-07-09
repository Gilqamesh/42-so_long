/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 15:35:20 by edavid            #+#    #+#             */
/*   Updated: 2021/07/09 09:42:16 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COLORS_H
# define FT_COLORS_H

typedef struct	s_node
{
	int				value;
	char			*name;
	struct s_node	*next;
}				t_node;

extern t_node	mlx_red;
extern t_node	mlx_purple;
extern t_node	mlx_blue;
extern t_node	mlx_cyan;
extern t_node	mlx_green;
extern t_node	mlx_yellow;
extern t_node	mlx_white;
extern t_node	mlx_black;

typedef struct	s_rgba
{
	unsigned char	alpha;
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
}				t_rgba;

typedef struct	s_hsl
{
	int		hue;
	char	saturation;
	char	lightness;	
}				t_hsl;

void	init_rainbow(void);
t_rgba	hex_to_rgba(int hex);
int		rgba_to_hex(t_rgba rgba);
t_rgba	make_rgba(int red, int green, int blue, int alpha);
t_hsl	make_hsl(int hex);
t_hsl	rgba_to_hsl(t_rgba rgba);
t_rgba	hsl_to_rgba(t_hsl hsl);
int		shade_add(double shade, int color);
int		get_red_from_hex(int hex);
int		get_green_from_hex(int hex);
int		get_blue_from_hex(int hex);
int		opposite_color_get(int hex);

#endif
