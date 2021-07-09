/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_testers.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 13:45:45 by edavid            #+#    #+#             */
/*   Updated: 2021/07/09 14:51:09 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TESTERS_H
# define FT_TESTERS_H

# include "ft_hooks.h"
# include "ft_utils.h"
typedef struct	s_mystruct
{
	t_vars	*vars;
	t_data	*img;
	int		*x;
	int		*y;
	int		*prev_x;
	int		*prev_y;
}				t_mystruct;

int		shader(t_data *img);
int		gradient_opposite(t_mystruct *mystruct);
int		color_changer(t_mystruct *mystruct);

#endif
