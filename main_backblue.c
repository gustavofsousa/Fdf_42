#include "./mlx/mlx.h"
#include <stdlib.h>

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	int		bits_per_pixel;//32
	int		line_bytes;
	int		endian;
}	t_data;

void	put_pixel_char(int pixel, int endian, int color, int *buffer)
{//If need to use this check the tutorial. Line_bytes would need to change.
	//if (data.bits_per_pixel != 32)
	//	color = mlx_get_color_value(data.mlx, color);
			//pixel = (y * line_bytes) + (x * 4);

    		if (endian == 1)        // Most significant (Alpha) byte first
    		{
        		buffer[pixel + 0] = (color >> 24);
        		buffer[pixel + 1] = (color >> 16) & 0xFF;
        		buffer[pixel + 2] = (color >> 8) & 0xFF;
        		buffer[pixel + 3] = (color) & 0xFF;
    		}
    		else if (endian == 0)   // Least significant (Blue) byte first
    		{
        		buffer[pixel + 0] = (color) & 0xFF;
        		buffer[pixel + 1] = (color >> 8) & 0xFF;
        		buffer[pixel + 2] = (color >> 16) & 0xFF;
        		buffer[pixel + 3] = (color >> 24);
    		}
}

int	main(void)
{
	int	x;
	int	y;
	int	color;
	//int	*buffer;

	t_data data;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, 640, 360, "red window");
	data.img = mlx_new_image(data.mlx, 640, 360);
	int	*buffer = (int *)mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_bytes, &data.endian);
	color = 0xABCDEF;
	data.line_bytes /= 4;
	y = 0;
	while (y < 360)
	{
		x = 0;
		while (x < 640)
		{
			buffer[(y * data.line_bytes) + x] = color;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_loop(data.mlx);
	return (0);
}
