#include "./mlx/mlx.h"
#include <stdlib.h>

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	int		bits_per_pixel;//32
	int		line_len;
	int		endian;
}	t_data;

int	main(void)
{
	int	x;
	int	y;
	int	color;
	char	*buffer;
	int	line_bytes;

	t_data data;
	data.bits_per_pixel = 32;
	line_bytes = 128;
	data.endian = 1;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, 640, 360, "red window");
	data.img = mlx_new_image(data.mlx, 640, 360);
	data.img = malloc(640 * 4 * 360 * 4);

	buffer = mlx_get_data_addr(data.img, &data.bits_per_pixel, &line_bytes, &data.endian);


	color = 0xFF0000;
	y = 0;
	while (y < 360)//Lines
	{
		x = 0;
		while (x < 640)//columns
		{
			buffer[y + x] = color;

			x += data.bits_per_pixel / 8;
		}
		y += line_bytes / 32;
	}
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_loop(data.mlx);
	return (0);
}
