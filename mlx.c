/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 14:39:55 by gusousa           #+#    #+#             */
/*   Updated: 2022/09/20 16:50:12 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	add_mlx_hook(t_fdf *fdf)
{
	(void)fdf;	
}

int	display_mlx_win(t_fdf *fdf)
{
	fdf->mlx.mlx = mlx_init();
	if (fdf->mlx.mlx != NULL)
	{
		fdf->mlx.win = mlx_new_window(fdf->mlx.mlx, W_LENGHT, W_HEIGHT, "fdf");
		if (fdf->mlx.win != NULL)
		{
			fdf->mlx.img = mlx_new_image(fdf->mlx.mlx,  2 * W_LENGHT, 2 * W_HEIGHT);
			if (fdf->mlx.img != NULL)
			{
				fdf->mlx.buffer = (int *)mlx_get_data_addr(fdf->mlx.img,
					&fdf->mlx.bits_per_pixel,  &fdf->mlx.line_bytes, &fdf->mlx.endian);
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
