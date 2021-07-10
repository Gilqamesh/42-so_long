/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 10:01:50 by edavid            #+#    #+#             */
/*   Updated: 2021/07/10 13:58:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HOOKS_H
# define FT_HOOKS_H

# include "ft_structs.h"

int	key_hook(int keycode, t_vars *vars);
int mouse_hook(int button, int x, int y, t_vars *vars);
int	resize_msg(void);
int	move_circle(int keycode, t_mystruct *mystruct);

#endif
