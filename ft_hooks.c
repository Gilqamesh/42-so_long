/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 10:02:09 by edavid            #+#    #+#             */
/*   Updated: 2021/07/16 18:32:58 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "mlx/mlx.h"
#include "ft_hooks.h"
#include "ft_colors.h"
#include "ft_utils.h"
#include "libft/libft.h"
#include "ft_structs.h"

static void	init_neighbour_chars(t_node (*neighbour_chars)[4],
t_mystruct *mystruct, t_point *current_position)
{
	(**neighbour_chars).value = *(*(*mystruct->map + current_position->y - 1)
			+ current_position->x);
	(**neighbour_chars).name = "up_char";
	(**neighbour_chars).next = 0;
	(*(*neighbour_chars + 1)).value = *(*(*mystruct->map + current_position->y)
			+ current_position->x - 1);
	(*(*neighbour_chars + 1)).name = "left_char";
	(**neighbour_chars).next = 0;
	(*(*neighbour_chars + 2)).value = *(*(*mystruct->map + current_position->y
				+ 1) + current_position->x);
	(*(*neighbour_chars + 2)).name = "down_char";
	(*(*neighbour_chars + 2)).next = 0;
	(*(*neighbour_chars + 3)).value = *(*(*mystruct->map + current_position->y)
			+ current_position->x + 1);
	(*(*neighbour_chars + 3)).name = "right_char";
	(*(*neighbour_chars + 3)).next = 0;
}

static void	init_neighbour_chars2(t_node (*neighbour_chars)[4],
t_node **cur_node, t_point *previous_position, t_point *current_position)
{
	(*(*neighbour_chars)).next = *neighbour_chars + 1;
	(*(*neighbour_chars + 1)).next = *neighbour_chars + 2;
	(*(*neighbour_chars + 2)).next = *neighbour_chars + 3;
	(*(*neighbour_chars + 3)).next = *neighbour_chars;
	if (previous_position->y - 1 == current_position->y)
		*cur_node = *neighbour_chars + 3;
	else if (previous_position->x - 1 == current_position->x)
		*cur_node = *neighbour_chars;
	else if (previous_position->y + 1 == current_position->y)
		*cur_node = *neighbour_chars + 1;
	else if (previous_position->x + 1 == current_position->x)
		*cur_node = *neighbour_chars + 2;
	else
		*cur_node = *neighbour_chars;
}

void	get_next_position(t_mystruct *mystruct, t_point *current_position,
t_point *previous_position)
{
	t_node	neighbour_chars[4];
	t_node	*cur_node;
	int		i;
	char	*str;

	init_neighbour_chars(&neighbour_chars, mystruct, current_position);
	init_neighbour_chars2(&neighbour_chars, &cur_node, previous_position,
		current_position);
	i = -1;
	while (++i < 5 && cur_node->value == '1')
		cur_node = cur_node->next;
	if (i != 5)
	{
		*previous_position = *current_position;
		str = cur_node->name;
		if (!ft_strncmp(str, "up_char", 2))
			current_position->y -= 1;
		else if (!ft_strncmp(str, "left_char", 2))
			current_position->x -= 1;
		else if (!ft_strncmp(str, "down_char", 2))
			current_position->y += 1;
		else
			current_position->x += 1;
	}
}

static int	check_collision(t_mystruct *mystruct, struct s_three_points *ABC,
int *number_of_enemies, int *number_of_calls)
{
	int	i;

	i = -1;
	while (++i < *number_of_enemies)
	{
		if (*(*(*mystruct->map + (ABC->enemy_positions + i)->y)
				+ (ABC->enemy_positions + i)->x) == 'G'
			|| *(*(*mystruct->map + (ABC->enemy_positions + i)->y)
				+ (ABC->enemy_positions + i)->x) == 'P')
		{
			free(ABC->enemy_positions);
			free(ABC->enemy_previous_positions);
			*number_of_calls = 0;
			*number_of_enemies = 0;
			reset_map(mystruct);
			return (1);
		}
	}
	return (0);
}

int	patrol_enemy(t_mystruct *mystruct)
{
	static t_point	exit;
	static t_point	*enemy_positions;
	static t_point	*enemy_previous_positions;
	static int		number_of_enemies;
	static int		number_of_calls;

	if (*mystruct->need_reset || !number_of_calls)
	{
		get_exit_coords(mystruct, &exit);
		initialize_vars(&enemy_positions, &enemy_previous_positions,
			&number_of_enemies, mystruct);
	}
	if (number_of_calls == 9999)
		patrol_enemy2(mystruct, number_of_enemies, &(struct s_three_points){
			exit, enemy_positions, enemy_previous_positions});
	if (check_collision(mystruct, &(struct s_three_points){exit,
			enemy_positions, enemy_previous_positions}, &number_of_enemies,
		&number_of_calls))
		return (0);
	number_of_calls++;
	if (number_of_calls == 10000)
		number_of_calls = 1;
	return (0);
}
