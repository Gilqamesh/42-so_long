/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 15:54:29 by edavid            #+#    #+#             */
/*   Updated: 2021/07/16 15:58:15 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils3.h"
#include "ft_utils2.h"
#include <stdlib.h>

void	initialize_positions(t_mystruct *mystruct, t_point **positions, int number_of_enemies)
{
	int	cur_index;

	*positions = malloc(number_of_enemies * sizeof(**positions));
	cur_index = 0;
	for (int y = 0; y < mystruct->map_height; y++)
		for (int x = 0; x < mystruct->map_width; x++)
			if (*(*(*mystruct->map + y) + x) == 'C')
				*(*positions + cur_index++) = (t_point){x, y};
}

void	get_exit_coords(t_mystruct *mystruct, t_point *exit)
{
	for (int y = 0; y < mystruct->map_height; y++)
		for (int x = 0; x < mystruct->map_width; x++)
			if (*(*(*mystruct->map + y) + x) == 'E')
			{
				exit->x = x;
				exit->y = y;
				return ;
			}
}

void	initialize_vars(t_point **enemy_positions, t_point **enemy_previous_positions,
int *number_of_enemies, t_point *exit, t_mystruct *mystruct)
{
	get_exit_coords(mystruct, exit);
	*number_of_enemies = count_collectibles(mystruct);
	initialize_positions(mystruct, enemy_positions, *number_of_enemies);
	*enemy_previous_positions = malloc(*number_of_enemies * sizeof(*enemy_previous_positions));
	for (int i = 0; i < *number_of_enemies; i++)
	{
		(*enemy_previous_positions)[i].x = (*enemy_positions)[i].x + 1;
		(*enemy_previous_positions)[i].y = (*enemy_positions)[i].y;
	}
}
