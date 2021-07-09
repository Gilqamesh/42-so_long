/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 10:02:09 by edavid            #+#    #+#             */
/*   Updated: 2021/07/09 10:59:56 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "mlx/mlx.h"
#include "ft_hooks.h"

int	key_hook(int keycode, t_vars *vars)
{
	(void)vars;
	printf("keycode: %d\n", keycode);
	return (0);
}

int mouse_hook(t_vars *vars)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	printf("mouse: %d %d\n", x, y);
	(void)vars;
	return (0);
}
