/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 14:39:55 by gusousa           #+#    #+#             */
/*   Updated: 2022/09/28 10:26:53 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	key_press(int keycode, t_fdf *fdf)
{
	if (keycode == 53)
	{
		mlx_destroy_image(fdf->mlx.mlx, fdf->mlx.img);
		mlx_destroy_window(fdf->mlx.mlx, fdf->mlx.win);
		exit (0);
	}
	return (0);
}

static int	close_event(t_fdf *fdf)
{
	mlx_destroy_image(fdf->mlx.mlx, fdf->mlx.img);
	mlx_destroy_window(fdf->mlx.mlx, fdf->mlx.win);
	exit(0);
	return (0);
}

static void	add_mlx_hook(t_fdf *fdf)
{
	mlx_key_hook(fdf->mlx.win, key_press, fdf);
	mlx_hook(fdf->mlx.win, 17, 0, close_event, fdf);
}

int	display_mlx_win(t_fdf *fdf)
{
	fdf->mlx.mlx = mlx_init();
	if (fdf->mlx.mlx != NULL)
	{
		fdf->mlx.win = mlx_new_window(fdf->mlx.mlx, W_LENGHT * 1.13, W_HEIGHT * 1.45, "fdf");
		if (fdf->mlx.win != NULL)
		{
			fdf->mlx.img = mlx_new_image(fdf->mlx.mlx, W_LENGHT * 1.13, W_HEIGHT * 1.45);
			if (fdf->mlx.img != NULL)
			{
				fdf->mlx.buffer = (int *)mlx_get_data_addr(fdf->mlx.img,
						&fdf->mlx.bits_per_pixel, &fdf->mlx.line_bytes, &fdf->mlx.endian);
				fdf->mlx.line_bytes /= 4;
				mlx_put_image_to_window(fdf->mlx.mlx, fdf->mlx.win, fdf->mlx.img, 0, 0);
				add_mlx_hook(fdf);
				draw_win(fdf);
				mlx_loop(fdf->mlx.mlx);
				return (1);
			}
		}
	}
	return (0);
}
