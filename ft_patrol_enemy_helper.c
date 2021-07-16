/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_patrol_enemy_helper.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 17:44:31 by edavid            #+#    #+#             */
/*   Updated: 2021/07/16 18:02:06 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_linux/mlx.h"
#include "ft_utils.h"

static void	patrol_enemy3(t_mystruct *mystruct, struct s_three_points *ABC,
int i)
{
	get_next_position(mystruct, ABC->enemy_positions + i,
		ABC->enemy_previous_positions + i);
	*(*(*mystruct->map + (ABC->enemy_previous_positions + i)->y)
			+ (ABC->enemy_previous_positions + i)->x) = '0';
	if (*(*(*mystruct->map + (ABC->enemy_positions + i)->y)
			+ (ABC->enemy_positions + i)->x) == 'P')
		*(*(*mystruct->map + (ABC->enemy_positions + i)->y)
				+ (ABC->enemy_positions + i)->x) = 'G';
	else
		*(*(*mystruct->map + (ABC->enemy_positions + i)->y)
				+ (ABC->enemy_positions + i)->x) = 'C';
	mlx_put_image_to_window(mystruct->vars->mlx, mystruct->vars->win,
		(mystruct->all_images.images + 4)->img,
		(ABC->enemy_previous_positions + i)->x * CELL_SIZE_W,
		(ABC->enemy_previous_positions + i)->y * CELL_SIZE_W);
}

void	patrol_enemy2(t_mystruct *mystruct, int number_of_enemies,
struct s_three_points *ABC)
{
	int	i;

	i = -1;
	while (++i < number_of_enemies)
		patrol_enemy3(mystruct, ABC, i);
	*(*(*mystruct->map + ABC->exit.y) + ABC->exit.x) = 'E';
	mlx_put_image_to_window(mystruct->vars->mlx, mystruct->vars->win,
		(mystruct->all_images.images + 2)->img, ABC->exit.x * CELL_SIZE_W,
		ABC->exit.y * CELL_SIZE_H);
	i = -1;
	while (++i < number_of_enemies)
		mlx_put_image_to_window(mystruct->vars->mlx, mystruct->vars->win,
			(mystruct->all_images.images + 3)->img,
			(ABC->enemy_positions + i)->x * CELL_SIZE_W,
			(ABC->enemy_positions + i)->y * CELL_SIZE_W);
}
