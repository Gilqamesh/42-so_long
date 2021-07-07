/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_basic_shapes.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 15:33:54 by edavid            #+#    #+#             */
/*   Updated: 2021/07/07 18:32:46 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BASIC_SHAPES_H
# define FT_BASIC_SHAPES_H

typedef struct	s_point
{
	int	x;
	int	y;
}				t_point;

# include "ft_utils.h"
void	circle_put_quick(t_data *data, int a, int b, int radius);
void	circle_put_parametric(t_data *data, int a, int b, int radius);
void	line_put_parametric(t_data *data, int x1, int y1, int x2, int y2, int color, int iter_n);
void	square_put(t_data *data, int x1, int y1, int x2, int y2, int color, int iter_n, void (*line_fn)(t_data *data, int x1, int y1, int x2, int y2, int color, int iter_n));
void	triangle_put(t_data *data, t_point A, t_point B, t_point C, int color, int iter_n, void (*line_fn)(t_data *data, int x1, int y1, int x2, int y2, int color, int iter_n));
void	line_put_gradient(t_data *data, t_point A, t_point B, int color1, int color2, int iter_n);

#endif
