/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 15:37:24 by edavid            #+#    #+#             */
/*   Updated: 2021/07/13 14:12:38 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_H
# define FT_UTILS_H

# include "ft_structs.h"

void	my_mlx_pixel_put(t_data *data, double x, double y, int color);
int		round_to_nearest(double a);
int		abs_int(int a);
double	abs_double(double a);
double	max_of_3(double a, double b, double c);
double	min_of_3(double a, double b, double c);
void	resize_img(t_vars vars, t_data *img, int old_width, int old_height, int new_width, int new_height);
void	get_part_of_img(t_vars vars, t_data *img, t_point bot_left, t_point top_right);
void	*ft_realloc(void *src, size_t size);
void	free_map(char ***map, int n_of_pointers);
void	validate_map(char ***map, int rows, int cols);
void	initialize_map(char ***map, int *map_width, int *map_height, char *filePath);
void	draw_map(char ***map, int map_height, t_data *images, t_point *start_point, t_vars vars);

#endif
