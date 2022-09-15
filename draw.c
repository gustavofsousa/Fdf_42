/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 14:45:32 by gusousa           #+#    #+#             */
/*   Updated: 2022/09/15 20:10:27 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_abs(int	nbr)
{
	if (nbr < 0)
		return (-nbr);
	return (nbr);
}

void	draw_horiz(t_fdf *fdf, int point1, int point2)
{
	int	pos;
	int	c;

	c = 0;
	while (c < fdf->map.interval_col)
	{
		pos = (fdf->p.y * fdf->mlx.line_bytes) + fdf->p.x + c;
		if (point1 - point2 == 0)
		{
			if (point1 == 0)
				fdf->mlx.buffer[pos] = WHITE;
			else 
				fdf->mlx.buffer[pos] = BLUE;
		}
		else
			fdf->mlx.buffer[pos] = GREEN;
		c++;
	}
}

void	draw_vertic(t_fdf *fdf, int point1, int point2)
{
	int	pos;
	int	c;

	c = 0;
	while (c < fdf->map.interval_row)
	{
		pos = ((fdf->p.y + c) * fdf->mlx.line_bytes) + fdf->p.x;
		if (point1 - point2 == 0)
		{
			if (point1 == 0)
				fdf->mlx.buffer[pos] = WHITE;
			else
				fdf->mlx.buffer[pos] = BLUE;
		}
		else
			fdf->mlx.buffer[pos] = GREEN;
		c++;
	}
}

void	draw_win(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->map.rows - 1)
	{
		j = 0;
		fdf->p.x = 0;
		while (j < fdf->map.columns - 1)
		{
			if (j < fdf->map.columns - 1)
				draw_horiz(fdf, fdf->map.map[i][j], fdf->map.map[i][j + 1]);
			if (i < fdf->map.columns - 1)
				draw_vertic(fdf, fdf->map.map[i][j], fdf->map.map[i + 1][j]);
			if (fdf->p.x % fdf->map.interval_col == 0)
				j++;
			fdf->p.x += fdf->map.interval_col;
		}
		if (fdf->p.y % fdf->map.interval_row == 0)
			i++;
		fdf->p.y += fdf->map.interval_row;
	}
	mlx_put_image_to_window(fdf->mlx.mlx, fdf->mlx.win, fdf->mlx.img, 0, 0);
}
