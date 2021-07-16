/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_structs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 14:00:36 by edavid            #+#    #+#             */
/*   Updated: 2021/07/16 16:16:55 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRUCTS_H
# define FT_STRUCTS_H
# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080
# define CELL_SIZE_W 50
# define CELL_SIZE_H 50
# ifdef BONUS
#  define IS_BONUS 1
#  else
#  define IS_BONUS 0
# endif
# define IS_MOVING_UP (previous_position->y - 1 == current_position->y)
# define IS_MOVING_LEFT (previous_position->x - 1 == current_position->x)
# define IS_MOVING_DOWN (previous_position->y + 1 == current_position->y)
# define IS_MOVING_RIGHT (previous_position->x + 1 == current_position->x)
# define UP_CHAR (*(*(*mystruct->map + current_position->y - 1) + current_position->x))
# define LEFT_CHAR (*(*(*mystruct->map + current_position->y) + current_position->x - 1))
# define DOWN_CHAR (*(*(*mystruct->map + current_position->y + 1) + current_position->x))
# define RIGHT_CHAR (*(*(*mystruct->map + current_position->y) + current_position->x + 1))

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}	t_vars;

typedef struct s_images
{
	t_data	*img;
	t_data	*images;
	t_data	*numberImages;
	t_data	*playerMovement;
}	t_images;

typedef struct s_mystruct
{
	t_vars		*vars;
	t_images	all_images;
	t_point		*cur_position;
	int			*prev_x;
	int			*prev_y;
	int			map_width;
	int			map_height;
	char		***map;
	char		*filePath;
	int			*move_counter;
	int			*need_reset;
}	t_mystruct;

typedef struct s_node
{
	int				value;
	char			*name;
	struct s_node	*next;
}	t_node;

#endif
