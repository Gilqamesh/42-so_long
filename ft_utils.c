/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 15:39:04 by edavid            #+#    #+#             */
/*   Updated: 2021/07/15 19:32:56 by edavid           ###   ########.fr       */
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

void	resize_img(t_vars vars, t_data *img, t_point old_params, t_point new_params)
{
	t_data	new_img;
	double	ratio_w;
	double	ratio_h;

	ratio_w = (double)new_params.x / old_params.x;
	ratio_h = (double)new_params.y / old_params.y;
	new_img.img = mlx_new_image(vars.mlx, new_params.x, new_params.y);
	new_img.addr = mlx_get_data_addr(new_img.img, &new_img.bits_per_pixel, &new_img.line_length, &new_img.endian);
	for (int y = 0; y < old_params.y; y++)
		for (int x = 0; x < old_params.x; x++)
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

void	initialize_map(t_mystruct *mystruct)
{
	char	*line;
	int		fd;

	fd = open(mystruct->filePath, O_RDONLY);
	if (fd == -1)
		ft_error("open returned -1 fd");
	mystruct->map_height = 0;
	if (get_next_line(fd, &line) < 0)
		ft_error("get_next_line negative return value");
	mystruct->map_width = ft_strlen(line);
	*mystruct->map = malloc(++mystruct->map_height * sizeof(char *));
	*(*mystruct->map + mystruct->map_height - 1) = line;
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
		*mystruct->map = ft_realloc(*mystruct->map, ++mystruct->map_height * sizeof(char *));
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
			img_offset.x = CELL_SIZE_W * cur_character;
			img_offset.y = CELL_SIZE_H * cur_map_height;
			mlx_put_image_to_window(mystruct->vars->mlx, mystruct->vars->win, (*mystruct->all_images->images + 4)->img, img_offset.x, img_offset.y);
			if (cur_cell == '1') // WALL
				mlx_put_image_to_window(mystruct->vars->mlx, mystruct->vars->win, (*mystruct->all_images->images)->img, img_offset.x, img_offset.y);
			else if (cur_cell == '0') // EMPTY SPACE
				mlx_put_image_to_window(mystruct->vars->mlx, mystruct->vars->win, (*mystruct->all_images->images + 1)->img, img_offset.x, img_offset.y);
			else if (cur_cell == 'E') // MAP EXIT
				mlx_put_image_to_window(mystruct->vars->mlx, mystruct->vars->win, (*mystruct->all_images->images + 2)->img, img_offset.x, img_offset.y);
			else if (cur_cell == 'P') // PLAYER
			{
				mystruct->cur_position->x = cur_character;
				mystruct->cur_position->y = cur_map_height;
				mlx_put_image_to_window(mystruct->vars->mlx, mystruct->vars->win, mystruct->playerMovement->img, img_offset.x, img_offset.y);
			}
			else if (cur_cell == 'C') // COLLECTIBLE 
				mlx_put_image_to_window(mystruct->vars->mlx, mystruct->vars->win, (*mystruct->all_images->images + 3)->img, img_offset.x, img_offset.y);
			cur_cell = *(*(*mystruct->map + cur_map_height) + ++cur_character);
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
			my_mlx_pixel_put(&img, x, y, g_mlx_black.value);
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
		mlx_put_image_to_window(mystruct->vars->mlx, mystruct->vars->win, (*mystruct->all_images->numberImages + 10)->img, coords.x + i * 55, coords.y);
	i = -1;
	while (str[++i])
		mlx_put_image_to_window(mystruct->vars->mlx, mystruct->vars->win, (*mystruct->all_images->numberImages + str[i] - '0')->img, coords.x + i * 55, coords.y);
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

void	print_map(t_mystruct *mystruct)
{
	for (int y = 0; y < mystruct->map_height; y++)
	{
		for (int x = 0; x < mystruct->map_width; x++)
			printf("%c", *(*(*mystruct->map + y) + x));
		printf("\n");
	}
}

void	reset_map(t_mystruct *mystruct)
{
	free_map(mystruct->map, mystruct->map_height);
	initialize_map(mystruct);
	draw_map(mystruct);
	#ifdef BONUS
	number_put(0, (t_point){600, 600}, mystruct, *mystruct->move_counter);
	#endif
	*mystruct->move_counter = 0;
}
