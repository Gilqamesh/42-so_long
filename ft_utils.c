/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 15:39:04 by edavid            #+#    #+#             */
/*   Updated: 2021/07/14 15:17:01 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "ft_utils.h"
#include "mlx/mlx.h"
#include "ft_error.h"
#include "gnl/ft_get_next_line.h"
#include <fcntl.h>
#include <unistd.h>
#include "ft_colors.h"

void	my_mlx_pixel_put(t_data *data, double x, double y, int color)
{
	char	*dst;
	int		a;
	int		b;

	a = round_to_nearest(x);
	b = round_to_nearest(y);
	dst = data->addr + (b * data->line_length + a * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int		round_to_nearest(double a)
{
	if ((int)(a * 10) % 10 < 5)
		return ((int)a);
	return ((int)(a + 1));
}

int		abs_int(int a)
{
	if (a > 0)
		return (a);
	if (a == INT_MIN)
		return (INT_MAX);
	return (-a);
}

double	abs_double(double a)
{
	if (a > 0)
		return (a);
	return (-a);
}

double	max_of_3(double a, double b, double c)
{
	if (a > b)
	{
		if (a > c)
			return (a);
		else // b > c not possible, because a > b > c and c > a is a contradiction
			return (c);
	}
	else // b > a
	{
		if (b > c)
			return (b);
		else // a > c not possible, because b > a > c and c > b is a contradiction
			return (c);
	}
}

double	min_of_3(double a, double b, double c)
{
	if (a > b)
	{
		if (a > c)
		{
			if (b > c)
				return (c);
			else
				return (b); 
		}
		else
			return (b);
	}
	else
	{
		if (b > c)
		{
			if (a > c)
				return (c);
			else
				return (a);
		}
		else
			return (a);
	}
}

void	resize_img(t_vars vars, t_data *img, int old_width, int old_height, int new_width, int new_height)
{
	t_data	new_img;
	double	ratio_w;
	double	ratio_h;

	ratio_w = (double)new_width / old_width;
	ratio_h = (double)new_height / old_height;
	new_img.img = mlx_new_image(vars.mlx, new_width, new_height);
	new_img.addr = mlx_get_data_addr(new_img.img, &new_img.bits_per_pixel, &new_img.line_length, &new_img.endian);
	for (int y = 0; y < old_height; y++)
		for (int x = 0; x < old_width; x++)
			my_mlx_pixel_put(&new_img, x * ratio_w, y * ratio_h, *(int *)(img->addr + y * img->line_length + x * (img->bits_per_pixel / 8)));
	mlx_destroy_image(vars.mlx, img->img);
	*img = new_img;
}

void	get_part_of_img(t_vars vars, t_data *img, t_point bot_left, t_point top_right)
{
	t_data	new_img;
	new_img.img = mlx_new_image(vars.mlx, abs_int(top_right.x - bot_left.x), abs_int(bot_left.y - top_right.y));
	new_img.addr = mlx_get_data_addr(new_img.img, &new_img.bits_per_pixel, &new_img.line_length, &new_img.endian);
	for (int y = top_right.y, y_new = 0; y < bot_left.y; y++, y_new++)
		for (int x = bot_left.x, x_new = 0; x < top_right.x; x++, x_new++)
			my_mlx_pixel_put(&new_img, x_new, y_new, *(int *)(img->addr + y * img->line_length + x * (img->bits_per_pixel / 8)));
	mlx_destroy_image(vars.mlx, img->img);
	*img = new_img;
}

void	*ft_realloc(void *src, size_t size)
{
	void	*new;

	new = malloc(size);
	if (!new)
		return (src);
	if (!src)
		return (new);
	ft_memmove(new, src, size);
	free(src);
	return (new);
}

void	free_map(char ***map, int n_of_pointers)
{
	while (n_of_pointers--)
		free(*(*map + n_of_pointers));
	free(*map);
	*map = 0;
}

void	validate_map(char ***map, int rows, int cols)
{
	int		x;
	int		y;
	int		exit_exists;
	int		collectible_exists;
	int		player_exists;
	char	c;

	y = 0;
	exit_exists = 0;
	collectible_exists = 0;
	player_exists = 0;
	while (y < rows)
	{
		x = 0;
		while (x < cols)
		{
			c = *(*(*map + y) + x);
			if (c == 'C')
				collectible_exists = 1;
			else if (c == 'E')
				exit_exists = 1;
			else if (c == 'P')
				player_exists = 1;
			if (((x == 0 || x == cols - 1) && c != '1') ||
				((y == 0 || y == rows - 1) && c != '1'))
			{
				free_map(map, rows);
				ft_error("map is not enclosed by walls");
			}
			x++;
		}
		y++;
	}
	if (!exit_exists)
	{
		free_map(map, rows);
		ft_error("no exit on map");
	}
	if (!collectible_exists)
	{
		free_map(map, rows);
		ft_error("no collectible on map");
	}
	if (!player_exists)
	{
		free_map(map, rows);
		ft_error("no starting position on map");
	}
}

void	initialize_map(char ***map, int *map_width, int *map_height, char *filePath)
{
	char	*line;
	int		fd;

	fd = open(filePath, O_RDONLY);
	if (fd == -1)
		ft_error("open returned -1 fd");
	*map_height = 0;
	if (get_next_line(fd, &line) < 0)
		ft_error("get_next_line negative return value");
	*map_width = ft_strlen(line) - 2;
	while (*line != '\0')
	{
		*map = ft_realloc(*map, ++*map_height * sizeof(char *));
		*(*map + *map_height - 1) = line;
		if (get_next_line(fd, &line) < 0)
		{
			free_map(map, *map_height);
			ft_error("get_next_line negative return value");
		}
		if (*line && (int)ft_strlen(line) - 2 != *map_width)
		{
			free_map(map, *map_height);
			ft_error("map is not rectangular");
		}
	}
	free(line);
	validate_map(map, *map_height, *map_width + 2);
	close(fd);
}

void	draw_map(char ***map, int map_height, t_data *images, t_point *start_point, t_vars vars, t_data *playerMovement)
{
	
	int		cur_map_height;
	int		cur_character;
	char	cur_cell;
	t_point	img_offset;

	cur_map_height = 0;
	while (cur_map_height < map_height)
	{
		cur_character = 0;
		cur_cell = *(*(*map + cur_map_height) + cur_character);
		while (cur_cell != '\0')
		{
			img_offset.x = CELL_SIZE_W * cur_character;
			img_offset.y = CELL_SIZE_H * cur_map_height;
			if (cur_cell == '1') // WALL
				mlx_put_image_to_window(vars.mlx, vars.win, images[0].img, img_offset.x, img_offset.y);
			else if (cur_cell == '0') // EMPTY SPACE
				mlx_put_image_to_window(vars.mlx, vars.win, images[1].img, img_offset.x, img_offset.y);
			else if (cur_cell == 'E') // MAP EXIT
				mlx_put_image_to_window(vars.mlx, vars.win, images[2].img, img_offset.x, img_offset.y);
			else if (cur_cell == 'P') // PLAYER
			{
				start_point->x = cur_character;
				start_point->y = cur_map_height;
				mlx_put_image_to_window(vars.mlx, vars.win, playerMovement->img, img_offset.x, img_offset.y);
			}
			else if (cur_cell == 'C') // COLLECTIBLE 
				mlx_put_image_to_window(vars.mlx, vars.win, images[3].img, img_offset.x, img_offset.y);
			cur_cell = *(*(*map + cur_map_height) + ++cur_character);
		}
		cur_map_height++;
	}
}

t_data	get_blank_image(void *mlx_ptr, int width, int height)
{
	t_data	img;

	img.img = mlx_new_image(mlx_ptr, width, height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
			my_mlx_pixel_put(&img, x, y, mlx_black.value);
	return (img);
}

void	number_put(int n, int x, int y, t_mystruct2 *mystruct, int previous_n)
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
		mlx_put_image_to_window(mystruct->vars->mlx, mystruct->vars->win, (mystruct->numberImages + 10)->img, x + i * 55, y);
	i = -1;
	while (str[++i])
		mlx_put_image_to_window(mystruct->vars->mlx, mystruct->vars->win, (mystruct->numberImages + str[i] - '0')->img, x + i * 55, y);
	free(str);
	free(previous_str);
}

int	pow_int(int base, int exp)
{
	if (exp < 0)
		exp *= -1;
	if (base == 0)
		return (0);
	if (exp == 0)
		return (1);
	return (base * pow_int(base, exp - 1));
}

void	print_map(t_mystruct2 *mystruct)
{
	for (int y = 0; y < mystruct->map_height + 2; y++)
	{
		for (int x = 0; x < mystruct->map_width + 2; x++)
			printf("%c", *(*(*mystruct->map + y) + x));
		printf("\n");
	}
}

void	reset_map(t_mystruct2 *mystruct)
{
	free_map(mystruct->map, mystruct->map_height + 2);
	initialize_map(mystruct->map, &mystruct->map_width, &mystruct->map_height, mystruct->filePath);
	draw_map(mystruct->map, mystruct->map_height, mystruct->images, mystruct->cur_position, *mystruct->vars, mystruct->playerMovement);
	number_put(0, 600, 600, mystruct, *mystruct->move_counter);
	*mystruct->move_counter = 0;
}
