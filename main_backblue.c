/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_backblue.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:46:51 by gusousa           #+#    #+#             */
/*   Updated: 2022/09/07 13:50:11 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	count_rows(t_fdf fdf, char *file_name)
{
	int			fd;

	fd = open(file_name, O_RDONLY);
	while (get_next_line(fd))
			map.rows++;
	close(fd);
}

int	parse(t_fdf fdf, char *file_name)
{
	char		**map_char;
	int			a_row;

	count_rows(fdf, file_name);
	map_char = 0;
	map_char = malloc(map.rows * sizeof(char *));
	if (map_char != 0)
	{
		map.map = malloc(map.rows * sizeof(int *));
		if (map.map != 0)
		{
			fd = open(file_name,  O_RDONLY);
			a_row = -1;
			while (++a_row < map.rows)
				//Check for invalid map
			{
				map_char[a_row] = get_next_line(fd);
				map.map[a_row] = ft_split_int(map_char[a_row], ' ');
				map.columns = (int)ft_count_words_str(map_char[a_row], ' ');
				free(map_char[a_row]);
			}
			free(map_char);
			return (1);
		}
	}
	return (0);
}


int	main(int argc, char **argv)
{
	int			pos;
	int			i;
	int 		j;
	int			**map_int;
	t_map	map;
	t_fdf	fdf;

	if (argc != 2)
		ft_putendl_fd("Missing arguments", 1);

	//Initializing mlx, image and buffer.
	fdf->mlx.mlx = mlx_init();
	fdf->mlx.win = mlx_new_window(fdf->mlx.mlx, W_LENGHT, W_HEIGHT, "fdf");
	fdf->mlx.img = mlx_new_image(fdf->mlx.mlx, W_LENGHT - 50, W_HEIGHT - 50);
	fdf->mlx.buffer = (int *)mlx_get_data_addr(fdf->mlx.img, &fdf->mlx.bits_per_pixel, &fdf->mlx.line_bytes, &fdf->mlx.endian);
	fdf->mlx.line_bytes /= 4;

	fdf->map.rows = 0;
	fdf->map.columns = 0;
	parse(fdf, argv[1]);


	int stack_interval_row = W_HEIGHT / fdf->map.rows;
	int stack_interval_col = W_LENGHT / fdf->map.columns;

	//Initializing pixel and color & paint.
	t_pixel pixel;
	pixel.color = GREEN_1;
	pixel.y = -1;
	i = 0;
	while (++pixel.y < W_HEIGHT - 50)
	{
		j = 0;
		pixel.x = -1;
		while (++pixel.x < W_LENGHT - 50)
		{
			if (pixel.y  % stack_interval_row == 0 || pixel.x % stack_interval_col == 0)
			{
				pos = (pixel.y * data.line_bytes) + pixel.x;
				if (map_int[i][j] != 0)
					data.buffer[pos] = PINK;
				else
					data.buffer[pos] = pixel.color;
				if (pixel.x % stack_interval_col == 0)
					j++;
			}
		}
		if (pixel.y % stack_interval_row == 0)
			i++;
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
