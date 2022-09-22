/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 14:39:55 by gusousa           #+#    #+#             */
/*   Updated: 2022/09/22 15:21:11 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_press(int keycode, t_fdf *fdf)
{
	if (keycode == 53)
		mlx_destroy_window(fdf->mlx.mlx, fdf->mlx.img);
	exit (0);
}

int	mouse_event(t_fdf *fdf)
{
	mlx_destroy_window(fdf->mlx.mlx, fdf->mlx.img);
	exit (0);
}

static void	add_mlx_hook(t_fdf *fdf)
{
	mlx_loop_hook(fdf->mlx.mlx, key_press, fdf);
	mlx_hook(fdf->mlx.mlx, 2, 0, key_press, fdf);
	mlx_hook(fdf->mlx.mlx, 17, 0, mouse_event, fdf);
}

int	display_mlx_win(t_fdf *fdf)
{
	fdf->mlx.mlx = mlx_init();
	if (fdf->mlx.mlx != NULL)
	{
		fdf->mlx.win = mlx_new_window(fdf->mlx.mlx, W_LENGHT + 150, W_HEIGHT + 300, "fdf");
		if (fdf->mlx.win != NULL)
		{
			fdf->mlx.img = mlx_new_image(fdf->mlx.mlx, 2 * W_LENGHT, 2 * W_HEIGHT);
			if (fdf->mlx.img != NULL)
			{
				fdf->mlx.buffer = (int *)mlx_get_data_addr(fdf->mlx.img,
						&fdf->mlx.bits_per_pixel, &fdf->mlx.line_bytes, &fdf->mlx.endian);
				fdf->mlx.line_bytes /= 4;
				add_mlx_hook(fdf);
				draw_win(fdf);
				mlx_loop(fdf->mlx.mlx);
				return (1);
			}
		}
	}
	return (0);
}
