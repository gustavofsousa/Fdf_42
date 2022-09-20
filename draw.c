/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 14:45:32 by gusousa           #+#    #+#             */
/*   Updated: 2022/09/20 17:43:33 by gusousa          ###   ########.fr       */
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

t_point	create_point(int x, int y, int z)
{
	t_point	p;
	p.x = x;
	p.y = y;
	p.z = z;
	return (p);
}

t_point	do_isometric(t_fdf *fdf, int z)
{
	double	angle = 2.0944;// 120;
	double	alpha = 0.5236;// 30
	//double	angle = 1.0472;// 60;
	t_point	rtn;
		
	rtn.x = fdf->p.x * cos(alpha)
			+ fdf->p.y * cos(alpha + angle)
			+ z * cos(alpha - angle);
	rtn.y = fdf->p.x * sin(alpha)
			+ fdf->p.y * sin(alpha + angle)
			+ z * sin(alpha - angle);
	return (rtn);
}

void	draw_horiz(t_fdf *fdf, int p1_z, int p2_z)
{
	int	pos;
	int	c;
	t_point	screen;

	c = fdf->map.interval_col;
	while (c--)
	{
		screen = do_isometric(fdf, p1_z);
		pos = (screen.y * fdf->mlx.line_bytes) + screen.x;
		if (p1_z - p2_z == 0)
			if (p1_z == 0)
				fdf->mlx.buffer[pos] = WHITE;
			else 
				fdf->mlx.buffer[pos] = BLUE;
		else
			fdf->mlx.buffer[pos] = GREEN;
		fdf->p.x++;
	}
	fdf->p.x -= fdf->map.interval_col;
}

void	draw_vertic(t_fdf *fdf, int p1_z, int p2_z)
{
	int	pos;
	int	c;
	t_point	screen;

	c = fdf->map.interval_row;
	while (c--)
	{
		screen = do_isometric(fdf, p1_z);
		pos = (screen.y * fdf->mlx.line_bytes) + screen.x;
		if (p1_z - p2_z == 0)
			if (p1_z == 0)
				fdf->mlx.buffer[pos] = WHITE;
			else
				fdf->mlx.buffer[pos] = BLUE;
		else
			fdf->mlx.buffer[pos] = GREEN;
		fdf->p.y++;
	}
	fdf->p.y -= fdf->map.interval_row;
}

void	draw_win(t_fdf *fdf)
{
	t_point	p;
	int	i;
	int	j;

	i = 0;
	while (i < fdf->map.rows - 1)
	{
		j = 0;
		fdf->p.x = 0;
		while (j < fdf->map.columns - 1)
		{
//			xs = fdf->p.x * cos(alpha) + fdf->p.y * cos(alpha + angle) + fdf->map.map[i][j] * cos(alpha - angle);
//			ys = fdf->p.x * sin(alpha) + fdf->p.y * sin(alpha + angle) + fdf->map.map[i][j] * sin(alpha - angle);
//			pos = (ys * fdf->mlx.line_bytes) + xs;
			p = create_point(fdf->p.x, fdf->p.y, fdf->map.map[i][j]);

			if (j < fdf->map.columns - 1)
				draw_horiz(fdf, p.z, fdf->map.map[i][j + 1]);
			if (i < fdf->map.columns - 1)
				draw_vertic(fdf, p.z, fdf->map.map[i + 1][j]);
			if (p.x % fdf->map.interval_col == 0)
				j++;
			fdf->p.x += fdf->map.interval_col;
		}
		if (p.y % fdf->map.interval_row == 0)
			i++;
		fdf->p.y += fdf->map.interval_row;
	}
	mlx_put_image_to_window(fdf->mlx.mlx, fdf->mlx.win, fdf->mlx.img, 0, 0);
}

