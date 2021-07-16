/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edavid <edavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 18:56:30 by edavid            #+#    #+#             */
/*   Updated: 2021/07/16 19:29:15 by edavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "ft_utils.h"
#include "ft_error.h"
#include "gnl/ft_get_next_line.h"

static void	check_error(t_point exit_collectible, int player_exists,
char ***map, int rows)
{
	if (!exit_collectible.x)
	{
		free_map(map, rows);
		ft_error("no exit on map");
	}
	if (!exit_collectible.y)
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

static void	set_vars_to_zero(t_point *A, t_point *B, int *player_exists)
{
	A->y = -1;
	B->x = 0;
	B->y = 0;
	*player_exists = 0;
}

static void	validate_map_helper(t_point *B, char c)
{
	if (c == 'C')
		B->y = 1;
	else if (c == 'E')
		B->x = 1;
}

void	validate_map(char ***map, int rows, int cols)
{
	t_point	A;
	t_point	B;
	int		player_exists;
	char	c;

	set_vars_to_zero(&A, &B, &player_exists);
	while (++A.y < rows)
	{
		A.x = -1;
		while (++A.x < cols)
		{
			c = *(*(*map + A.y) + A.x);
			validate_map_helper(&B, c);
			if (c == 'P')
				player_exists = 1;
			if (((A.x == 0 || A.x == cols - 1) && c != '1')
				|| ((A.y == 0 || A.y == rows - 1) && c != '1'))
			{
				free_map(map, rows);
				ft_error("map is not enclosed by walls");
			}
		}
	}
	check_error(B, player_exists, map, rows);
}

void	init_map_helper(t_mystruct *mystruct, char **line, int *fd)
{
	*fd = open(mystruct->filePath, O_RDONLY);
	if (*fd == -1)
		ft_error("open returned -1 fd");
	mystruct->map_height = 0;
	if (get_next_line(*fd, line) < 0)
		ft_error("get_next_line negative return value");
	mystruct->map_width = ft_strlen(*line);
	*mystruct->map = malloc(++mystruct->map_height * sizeof(char *));
	*(*mystruct->map + mystruct->map_height - 1) = *line;
}
