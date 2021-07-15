/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 10:01:50 by edavid            #+#    #+#             */
/*   Updated: 2021/07/15 14:32:40 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HOOKS_H
# define FT_HOOKS_H

# include "ft_structs.h"

int	key_hook(int keycode, t_vars *vars);
int	mouse_hook(int button, int x, int y, t_vars *vars);
int	move_circle(int keycode, t_mystruct *mystruct);
int	move_ninja(int keycode, t_mystruct2 *mystruct);
int	exit_clicked(t_mystruct2 *mystruct);
int	patrol_enemy(t_mystruct2 *mystruct);

#endif
