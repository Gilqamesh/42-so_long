/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 15:37:24 by edavid            #+#    #+#             */
/*   Updated: 2021/07/16 19:19:35 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_H
# define FT_UTILS_H

# include "ft_structs.h"
# include <stdlib.h>
void	my_mlx_pixel_put(t_data *data, double x, double y, int color);
int		round_to_nearest(double a);
int		abs_int(int a);
double	abs_double(double a);
double	max_of_3(double a, double b, double c);
double	min_of_3(double a, double b, double c);
void	resize_img(t_vars vars, t_data *img, t_point old_params,
			t_point new_params);
void	get_part_of_img(t_vars vars, t_data *img, t_point bot_left,
			t_point top_right);
void	*ft_realloc(void *src, size_t size);
void	free_map(char ***map, int n_of_pointers);
void	validate_map(char ***map, int rows, int cols);
void	initialize_map(t_mystruct *mystruct);
void	draw_map(t_mystruct *mystruct);
t_data	get_blank_image(void *mlx_ptr, int width, int height);
void	number_put(int n, t_point coords, t_mystruct *mystruct,
			int previous_n);
int		pow_int(int base, int exp);
void	print_map(t_mystruct *mystruct);
void	reset_map(t_mystruct *mystruct);
int		wasd_pressed(int keycode, t_mystruct *mystruct);
int		all_collected(char ***map, int width, int height);
int		exit_clicked(t_mystruct *mystruct);
int		count_collectibles(t_mystruct *mystruct);
void	initialize_positions(t_mystruct *mystruct, t_point **positions,
			int number_of_enemies);
void	get_exit_coords(t_mystruct *mystruct, t_point *exit);
void	initialize_vars(t_point **enemy_positions,
			t_point **enemy_previous_positions, int *number_of_enemies,
			t_mystruct *mystruct);
void	get_next_position(t_mystruct *mystruct, t_point *current_position,
			t_point *previous_position);
void	init_map_helper(t_mystruct *mystruct, char **line, int *fd);
void	draw_map_helper(t_mystruct *mystruct, int cur_map_height,
			int cur_character, int cur_cell);

#endif
