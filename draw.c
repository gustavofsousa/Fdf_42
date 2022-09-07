/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 14:45:32 by gusousa           #+#    #+#             */
/*   Updated: 2022/09/07 15:10:15 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    draw_win(t_fdf *fdf)
{
	int                     pos;
	int                     i;
	int             j;
	int stack_interval_row = W_HEIGHT / fdf->map.rows;
	int stack_interval_col = W_LENGHT / fdf->map.columns;

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
				pos = (pixel.y * fdf->mlx.line_bytes) + pixel.x;
				if (fdf->map.map[i][j] != 0)
					fdf->mlx.buffer[pos] = PINK;
				else
					fdf->mlx.buffer[pos] = pixel.color;
				if (pixel.x % stack_interval_col == 0)
					j++;
			}
		}
		if (pixel.y % stack_interval_row == 0)
			i++;
	}
	mlx_put_image_to_window(fdf->mlx.mlx, fdf->mlx.win, fdf->mlx.img, 30, 30);
}
