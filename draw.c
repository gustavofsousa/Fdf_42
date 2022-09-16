/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 14:45:32 by gusousa           #+#    #+#             */
/*   Updated: 2022/09/16 12:02:33 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

int	ft_abs(int	nbr)
{
	if (nbr < 0)
		return (-nbr);
	return (nbr);
}

void	do_isometric(t_fdf *fdf)
{
	// x é n_columns
	// y is n_row
	// z is map[i][j]
	// alpha is 30 degree(to radians)
	
	double	angle = 2.0944;
	double	alpha = 0.5236;
	double	u;
	double	v;
	int		x;
	int		y;
	int		z;

	x = fdf->map.i;
	y = fdf->map.j;
	u = x * cos(alpha) + y * cos(alpha + 120) + fdf->map.z * cos(alpha - 120);
	v = x * sen(alpha) + y * sen(alpha + 120) + fdf->map.z * sen(alpha - 120);
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

// Colocar a mesma função, diferenciar só a pos
// Fazer struct com ponto. x y z.
// Ao mudar a pos, já fazer multiplicar pelo resultado do isometric.

void	draw_win(t_fdf *fdf)
{
	t_point	p1;
	t_point	p2;
	fdf->map.i = 0;
	while (fdf->map.i < fdf->map.rows - 1)
	{
		j = 0;
		fdf->p.x = 0;
		while (fdf->map.j < fdf->map.columns - 1)
		{
			if (fdf->map.j < fdf->map.columns - 1)
				draw_horiz(fdf, (t_point){i, j, fdf->map.map[i][j]}, (t_point){i, j, fdf->map.map[i][j + 1]});
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
