/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_structs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 14:00:36 by edavid            #+#    #+#             */
/*   Updated: 2021/07/12 14:00:38 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRUCTS_H
# define FT_STRUCTS_H

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_vars
{
	void	*mlx;
	void	*win;
}				t_vars;

typedef struct	s_mystruct
{
	t_vars	*vars;
	t_data	*img;
	int		*x;
	int		*y;
	int		*prev_x;
	int		*prev_y;
}				t_mystruct;

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

typedef struct	s_node
{
	int				value;
	char			*name;
	struct s_node	*next;
}				t_node;

typedef struct	s_point
{
	int	x;
	int	y;
}				t_point;

#endif
