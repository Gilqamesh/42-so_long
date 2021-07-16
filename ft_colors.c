/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 16:17:06 by edavid            #+#    #+#             */
/*   Updated: 2021/07/16 11:06:39 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_colors.h"
#include "ft_utils.h"

t_node	g_mlx_red = {0x00FF0000, "red", 0};
t_node	g_mlx_purple = {0x00FF00FF, "purple", 0};
t_node	g_mlx_blue = {0x000000FF, "blue", 0};
t_node	g_mlx_cyan = {0x0000FFFF, "cyan", 0};
t_node	g_mlx_green = {0x0000FF00, "green", 0};
t_node	g_mlx_yellow = {0x00FFFF00, "yellow", 0};
t_node	g_mlx_white = {0x00FFFFFF, "white", 0};
t_node	g_mlx_black = {0x00000000, "black", 0};

void	init_rainbow(void)
{
	g_mlx_red.next = &g_mlx_purple;
	g_mlx_purple.next = &g_mlx_blue;
	g_mlx_blue.next = &g_mlx_cyan;
	g_mlx_cyan.next = &g_mlx_green;
	g_mlx_green.next = &g_mlx_yellow;
	g_mlx_yellow.next = &g_mlx_red;
}
