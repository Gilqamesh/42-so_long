/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 15:35:20 by edavid            #+#    #+#             */
/*   Updated: 2021/07/07 17:05:23 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COLORS_H
# define FT_COLORS_H

typedef struct	s_node
{
	int				value;
	char			*name;
	struct s_node	*next;
}				t_node;

extern t_node	mlx_red;
extern t_node	mlx_purple;
extern t_node	mlx_blue;
extern t_node	mlx_cyan;
extern t_node	mlx_green;
extern t_node	mlx_yellow;
extern t_node	mlx_white;
extern t_node	mlx_black;

void	init_rainbow(void);

#endif
