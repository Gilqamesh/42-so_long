#include "mlx/mlx.h"
#define PRINT_ERROR(s) printf("%s at line %d\n", __LINE__);return (-1)

int main(void)
{
	void	*mlx;
	void	*mlx_window;

	// initialize MiniLibX, store the location of the MLX instance in mlx var
	mlx = mlx_init();
	if (!mlx)
		PRINT_ERROR("mlx_init failed");

	// create a window with specified dimensions and title, and store the location in mlx_window var
	mlx_window = mlx_new_window(mlx, 1920, 1080, "Hello World!");
	if (!mlx_window)
		PRINT_ERROR("mlx_window failed");

	// to initiate the window rendering
	mlx_loop(mlx);
}
