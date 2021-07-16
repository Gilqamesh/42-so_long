/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 10:01:50 by edavid            #+#    #+#             */
/*   Updated: 2021/07/16 18:22:00 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HOOKS_H
# define FT_HOOKS_H

# include "ft_structs.h"
int		move_ninja(int keycode, t_mystruct *mystruct);
int		patrol_enemy(t_mystruct *mystruct);
void	patrol_enemy2(t_mystruct *mystruct, int number_of_enemies,
			struct s_three_points *ABC);

#endif
