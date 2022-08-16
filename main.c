#include <stdlib.h>
#include "./mlx/mlx.h"

int main(void)
{
	void	*mlx_ptr;
	void *mlx_win;

	mlx_ptr = mlx_init();
	mlx_win = mlx_new_window(mlx_ptr, 640,
			430, "so_long");
	mlx_loop(mlx_ptr);
}
