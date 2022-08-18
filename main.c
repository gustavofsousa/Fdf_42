#include <stdlib.h>
#include "./mlx/mlx.h"

//#include <X11/X.h>
//#include <X11/keysym.h>
//#include <mlx.h>

#define W_WIDTH 600
#define W_HEIGHT 300
#define RED_PIXEL 0xFF0000

typedef struct s_data
{
	void	*mlx;
	void	*mlx_win;
}	t_data;

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == 53)
	{
		mlx_destroy_window(data->mlx, data->mlx_win);
		data->mlx_win = NULL;
	}
	return (0);
}


typedef struct s_rect
{
	int	x;
	int	y;
	int width;
	int height;
	int color;
}	t_rect;

int render_rect(t_data *data, t_rect rect)
{
	int	i;
	int j;

	if (data->mlx_win == NULL)
		return (1);
	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
			mlx_pixel_put(data->mlx, data->mlx_win, j++, i, rect.color);
		++i;
	}
	return (0);
}

int	render(t_data *data)
{
	render_rect(data, (t_rect){W_WIDTH - 100, W_HEIGHT - 100,
			100, 100, RED_PIXEL});
	render_rect(data, (t_rect){0, 0, 100, 100, RED_PIXEL});

	return (0);
}


int main(void)
{
	t_data	data;

	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, W_WIDTH, W_HEIGHT, "fdf");

	//mlx_loop_hook(data.mlx, &render, &data);
	mlx_key_hook(data.mlx_win, handle_keypress, &data);

	mlx_loop(data.mlx);

	//mlx_destroy_window(data.mlx);
	//free(data.mlx);
}
