/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 16:17:06 by edavid            #+#    #+#             */
/*   Updated: 2021/07/07 17:05:58 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_colors.h"

t_node	mlx_red = {0x00FF0000, "red", 0};
t_node	mlx_purple = {0x00FF00FF, "purple", 0};
t_node	mlx_blue = {0x000000FF, "blue", 0};
t_node	mlx_cyan = {0x0000FFFF, "cyan", 0};
t_node	mlx_green = {0x0000FF00, "green", 0};
t_node	mlx_yellow = {0x00FFFF00, "yellow", 0};
t_node	mlx_white = {0x00000000, "white", 0};
t_node	mlx_black = {0x00FFFFFF, "black", 0};

void	init_rainbow(void)
{
	mlx_red.next = &mlx_purple;
	mlx_purple.next = &mlx_blue;
	mlx_blue.next = &mlx_cyan;
	mlx_cyan.next = &mlx_green;
	mlx_green.next = &mlx_yellow;
	mlx_yellow.next = &mlx_red;
}
