#inclue "mlx/mlx.h"

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	int		bits_per_pixel;//32
	int		line_len;
	int		endian;
}	t_data;

void	main(void)
{

	int	x;
	int	y;
	int	color;
	int	*buffer;
	int	line_bytes;

	t_data data;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, 640, 360, "red window");
	data.img = mlx_new_image(data.mlx, 640, 360);

	buffer = mlx_get_data_addr(data.img, 32, 1, data.endian);


	color = 0xFF0000;
	line_bytes = 100;
	y = -1;
	while (++y < 360)//Lines
	{
		x = -1;
		while (++x < 640)//columns
		{
			buffer[(y * line_bytes) + x] = color;





		}

	}
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_loop(data.mlx);
	return (0);
}
