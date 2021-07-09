/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 10:01:50 by edavid            #+#    #+#             */
/*   Updated: 2021/07/09 15:02:24 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HOOKS_H
# define FT_HOOKS_H

typedef struct	s_vars
{
	void	*mlx;
	void	*win;
}				t_vars;

# include "ft_testers.h"
int	key_hook(int keycode, t_vars *vars);
int mouse_hook(int button, int x, int y, t_vars *vars);
int	resize_msg(void);
int	move_circle(int keycode, t_mystruct *mystruct);

#endif
