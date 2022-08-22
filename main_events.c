#include <stdio.h>
#include <stdlib.h>
#include "./mlx/mlx.h"
//#include <X11/X.h>
//#include <X11/keysym.h>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 300

#define MLX_ERROR 1

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_data;

int	handle_no_event(void *data)
{
	/* This function needs to exist, but it is useless for the moment */
	(void)data;
	return (0);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == 53)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	(void)data;

	printf("Keypress: %d\n", keysym);
	return (0);
}
// It's functional but I can't escape. Trid that if (down) to do so. Error.
int	handle_keyrelease(int keysym, void *data)
{
	void	*ptr;
	void	*win;

	(void)data;
	printf("Keyrelease: %d\n", keysym);
	ptr = data->mlx_ptr;
	win = data->win_ptr;
	if (keysym == 53)
		mlx_destroy_window(ptr, win);
	return (0);
}

int	main(void)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "My first window!");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (MLX_ERROR);
	}

	/* Setup hooks */ 
	mlx_loop_hook(data.mlx_ptr, &handle_no_event, &data);
	mlx_hook(data.win_ptr, 2, 1L << 2, &handle_keypress, &data); /* CHANGED */
	mlx_hook(data.win_ptr, 2, 1L << 2, &handle_keyrelease, &data); /* CHANGED */

	mlx_loop(data.mlx_ptr);

	/* we will exit the loop if there's no window left, and execute this code */
	//mlx_destroy_window(data.mlx_ptr, data.win_ptr);
	free(data.mlx_ptr);
}
