/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 15:54:29 by edavid            #+#    #+#             */
/*   Updated: 2021/07/16 18:36:31 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "ft_utils.h"

void	initialize_positions(t_mystruct *mystruct, t_point **positions,
int number_of_enemies)
{
	int	cur_index;
	int	y;
	int	x;

	*positions = malloc(number_of_enemies * sizeof(**positions));
	cur_index = 0;
	y = -1;
	x = -1;
	while (++y < mystruct->map_height)
	{
		while (++x < mystruct->map_width)
			if (*(*(*mystruct->map + y) + x) == 'C')
				*(*positions + cur_index++) = (t_point){x, y};
		x = -1;
	}
}

void	get_exit_coords(t_mystruct *mystruct, t_point *exit)
{
	int	y;
	int	x;

	y = -1;
	x = -1;
	while (++y < mystruct->map_height)
	{
		while (++x < mystruct->map_width)
		{
			if (*(*(*mystruct->map + y) + x) == 'E')
			{
				exit->x = x;
				exit->y = y;
				return ;
			}
		}
		x = -1;
	}
}

void	initialize_vars(t_point **enemy_positions,
t_point **enemy_previous_positions, int *number_of_enemies,
t_mystruct *mystruct)
{
	int	i;

	*number_of_enemies = count_collectibles(mystruct);
	initialize_positions(mystruct, enemy_positions, *number_of_enemies);
	*enemy_previous_positions = malloc(*number_of_enemies
			* sizeof(*enemy_previous_positions));
	i = -1;
	while (++i < *number_of_enemies)
	{
		(*enemy_previous_positions)[i].x = (*enemy_positions)[i].x + 1;
		(*enemy_previous_positions)[i].y = (*enemy_positions)[i].y;
	}
}
