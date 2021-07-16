/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 15:35:20 by edavid            #+#    #+#             */
/*   Updated: 2021/07/16 10:45:26 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COLORS_H
# define FT_COLORS_H

# include "ft_structs.h"

extern t_node	g_mlx_red;
extern t_node	g_mlx_purple;
extern t_node	g_mlx_blue;
extern t_node	g_mlx_cyan;
extern t_node	g_mlx_green;
extern t_node	g_mlx_yellow;
extern t_node	g_mlx_white;
extern t_node	g_mlx_black;

void	init_rainbow(void);
int		shade_add(double shade, int color);
int		get_red_from_hex(int hex);
int		get_green_from_hex(int hex);
int		get_blue_from_hex(int hex);
int		opposite_color_get(int hex);

#endif
