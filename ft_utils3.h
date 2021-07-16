/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils3.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 15:54:48 by edavid            #+#    #+#             */
/*   Updated: 2021/07/16 15:57:45 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS3_H
# define FT_UTILS3_H

# include "ft_structs.h"
void	initialize_positions(t_mystruct *mystruct, t_point **positions, int number_of_enemies);
void	get_exit_coords(t_mystruct *mystruct, t_point *exit);
void	initialize_vars(t_point **enemy_positions, t_point **enemy_previous_positions,
		int *number_of_enemies, t_point *exit, t_mystruct *mystruct);

#endif
