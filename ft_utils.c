/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 15:39:04 by edavid            #+#    #+#             */
/*   Updated: 2021/07/16 19:32:16 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "ft_utils.h"
#include "mlx_linux/mlx.h"
#include "ft_error.h"
#include "gnl/ft_get_next_line.h"
#include <fcntl.h>
#include <unistd.h>
#include "ft_colors.h"
#include "libft/libft.h"

void	initialize_map(t_mystruct *mystruct)
{
	char	*line;
	int		fd;

	init_map_helper(mystruct, &line, &fd);
	while (*line != '\0')
	{
		if (get_next_line(fd, &line) < 0)
		{
			free_map(mystruct->map, mystruct->map_height);
			ft_error("get_next_line negative return value");
		}
		if (*line && (int)ft_strlen(line) != mystruct->map_width)
		{
			free_map(mystruct->map, mystruct->map_height);
			ft_error("map is not rectangular");
		}
		if (*line == '\0')
			break ;
		*mystruct->map = ft_realloc(*mystruct->map, ++mystruct->map_height
				* sizeof(char *));
		*(*mystruct->map + mystruct->map_height - 1) = line;
	}
	free(line);
	validate_map(mystruct->map, mystruct->map_height, mystruct->map_width);
	close(fd);
}

void	draw_map(t_mystruct *mystruct)
{
	int		cur_map_height;
	int		cur_character;
	char	cur_cell;
	t_point	img_offset;

	cur_map_height = 0;
	while (cur_map_height < mystruct->map_height)
	{
		cur_character = 0;
		cur_cell = *(*(*mystruct->map + cur_map_height) + cur_character);
		while (cur_cell != '\0')
		{
			draw_map_helper(mystruct, cur_map_height, cur_character, cur_cell);
			img_offset.x = CELL_SIZE_W * cur_character;
			img_offset.y = CELL_SIZE_H * cur_map_height;
			if (cur_cell == 'C')
				mlx_put_image_to_window(mystruct->vars->mlx,
					mystruct->vars->win, (mystruct->all_images.images + 3)->img,
					img_offset.x, img_offset.y);
			cur_cell = *(*(*mystruct->map + cur_map_height) + ++cur_character);
		}
		cur_map_height++;
	}
}

t_data	get_blank_image(void *mlx_ptr, int width, int height)
{
	t_data	img;
	int		y;
	int		x;

	img.img = mlx_new_image(mlx_ptr, width, height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	y = -1;
	while (++y < height)
	{
		x = -1;
		while (++x < width)
			my_mlx_pixel_put(&img, x, y, g_mlx_black.value);
	}
	return (img);
}

void	number_put(int n, t_point coords, t_mystruct *mystruct, int previous_n)
{
	char	*str;
	char	*previous_str;
	int		i;
	int		len;

	str = ft_itoa(n);
	previous_str = ft_itoa(previous_n);
	len = ft_strlen(previous_str);
	i = -1;
	while (++i < len)
		mlx_put_image_to_window(mystruct->vars->mlx, mystruct->vars->win,
			(mystruct->all_images.numberImages + 10)->img, coords.x + i * 55,
			coords.y);
	i = -1;
	while (str[++i])
		mlx_put_image_to_window(mystruct->vars->mlx, mystruct->vars->win,
			(mystruct->all_images.numberImages + str[i] - '0')->img, coords.x
			+ i * 55, coords.y);
	free(str);
	free(previous_str);
}

void	reset_map(t_mystruct *mystruct)
{
	free_map(mystruct->map, mystruct->map_height);
	initialize_map(mystruct);
	draw_map(mystruct);
	if (IS_BONUS)
		number_put(0, (t_point){600, 600}, mystruct, *mystruct->move_counter);
	*mystruct->move_counter = 0;
}
