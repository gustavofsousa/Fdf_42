/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 14:45:32 by gusousa           #+#    #+#             */
/*   Updated: 2022/09/15 14:57:32 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_abs(int	nbr)
{
	if (nbr < 0)
		return (-nbr);
	return (nbr);
}

void	draw_line(t_fdf *fdf, int i, int j)
{
	int	pos;

	if (fdf->p.y % fdf->map.interval_row == 0 || fdf->p.x % fdf->map.interval_col == 0)
	{
		pos = (i * fdf->mlx.line_bytes) + fdf->p.x;
		if (fdf->map.map[i][j] != 0)
			fdf->mlx.buffer[pos] = PINK;
		else
			fdf->mlx.buffer[pos] = fdf->p.color;
	}
}

void    draw_win_i(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (fdf->p.y < W_HEIGHT)
	{
		j = 0;
		while (fdf->p.x < i * W_LENGHT)
		{
//			if (i != 0 && j != 0)
				draw_line(fdf, i, j);
			if (fdf->p.x % fdf->map.interval_col == 0)
				j++;
			fdf->p.x++;
		}
		if (fdf->p.y % fdf->map.interval_row == 0)
			i++;
		fdf->p.y++;
	}
	mlx_put_image_to_window(fdf->mlx.mlx, fdf->mlx.win, fdf->mlx.img, 0, 0);
}

void	draw_win(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->map.rows)
	{
		j = 0;
		while (j < fdf->map.columns)
		{
			draw_line(fdf, i, j);
			if (fdf->p.x % fdf->map.interval_col == 0)
				j++;
			fdf->p.x++;
		}
		if (fdf->p.y % fdf->map.interval_row == 0)
			i++;
		fdf->p.y++;
	}
	mlx_put_image_to_window(fdf->mlx.mlx, fdf->mlx.win, fdf->mlx.img, 0, 0);
}
