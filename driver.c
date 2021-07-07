#include "mlx/mlx.h"
#include <math.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	circle_put(t_data *data, int middle, int radius, int color)
{
	char	*dst;
	int		i;

	// (X - x)^2 + (Y - y)^2 = R^2
	
}

int main(void)
{
	void	*mlx;
	void	*mlx_win;

	// initialize MiniLibX, store the location of the MLX instance in mlx var
	mlx = mlx_init();
	// create a window with specified dimensions and title, and store the location in mlx_win var
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello World!");

	t_data	img;

	// initialize image
	img.img = mlx_new_image(mlx, 1920, 1080);
	// call mlx_get_data_addr to set some of the vars of t_data
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	//circle_put();
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);

	// to initiate the window rendering
	mlx_loop(mlx);
}
