/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 15:45:15 by edavid            #+#    #+#             */
/*   Updated: 2021/07/16 15:54:45 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS2_H
# define FT_UTILS2_H

#include "ft_structs.h"
int		wasd_pressed(int keycode, t_mystruct *mystruct);
int		all_collected(char ***map, int width, int height);
int		exit_clicked(t_mystruct *mystruct);
int		count_collectibles(t_mystruct *mystruct);

#endif
