#include "fdf.h"

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	int		*buffer;//I put int*
	int		bits_per_pixel;//32
	int		line_bytes;
	int		endian;
}	t_data;

typedef struct	s_pixel
{
	int			x;
	int			y;
	int			color;
}				t_pixel;

int	main(void)
{
	int	pos;

	//Initializing mlx, image and buffer.
	t_data data;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, W_LENGHT, W_HEIGHT, "red window");
	data.img = mlx_new_image(data.mlx, W_LENGHT - 60, W_HEIGHT - 60);
	data.buffer = (int *)mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_bytes, &data.endian);
	data.line_bytes /= 4;

	//Initializing pixel and color
	t_pixel pixel;
	pixel.color = 0xABCDEF;
	pixel.y = 0;
	while (pixel.y < 360)
	{
		pixel.x = -1;
		while (++pixel.x < 640)
		{
			pos = (pixel.y * data.line_bytes) + pixel.x;
			data.buffer[pos] = pixel.color;
		}
		pixel.y++;
	}
	mlx_put_image_to_window(data.mlx, data.win, data.img, 30, 30);
	mlx_loop(data.mlx);
	return (0);
}





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
