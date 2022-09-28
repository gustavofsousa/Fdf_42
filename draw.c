/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 14:45:32 by gusousa           #+#    #+#             */
/*   Updated: 2022/09/28 11:29:49 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

t_point	create_point(int x, int y, int z)
{
	t_point	p;

	p.x = x;
	p.y = y;
	p.z = z;
	return (p);
}

t_point	do_isometric(t_point p)
{
	double	angle;
	double	alpha;
	t_point	rtn;

	alpha = 0.0174533 * 20; // 30					   
	angle = 0.0174533 * 120; //110
	rtn.x = p.x * cos(alpha)
		+ p.y * cos(alpha + angle)
		+ p.z * cos(alpha - angle);
	rtn.y = p.x * sin(alpha)
		+ p.y * sin(alpha + angle)
		+ p.z * sin(alpha - angle);
	return (rtn);
}

static void	define_increase(t_point p1, t_point p2, t_var_steep *stp)
{
	if (p2.x > p1.x)
		stp->xs = 1;
	else
		stp->xs = -1;
	if (p2.y > p1.y)
		stp->ys = 1;
	else
		stp->ys = -1;
	if (p2.z > p1.z)
		stp->zs = 1;
	else
		stp->zs = -1;
}

static void	advance_axis_X(t_fdf *fdf, t_var_steep stp, t_point p1, t_point p2)
{
	t_point	s1;
	int	pos;

	stp.pk1 = 2 * stp.dy - stp.dx;
	stp.pk2 = 2 * stp.dz - stp.dx;
	while (p1.x != p2.x)
	{
		p1.x += stp.xs;
		if (stp.pk1 >= 0)
		{
			p1.y += stp.ys;
			stp.pk1 -= 2 * stp.dx;
		}
		if (stp.pk2 >= 0)
		{
			p1.z += stp.zs;
			stp.pk2 -= 2 * stp.dx;
		}
		stp.pk1 += 2 * stp.dy;
		stp.pk2 += 2 * stp.dz;
		s1 = do_isometric(p1);
		pos = (s1.y * fdf->mlx.line_bytes) + s1.x + fdf->map.offset;
		fdf->mlx.buffer[pos] = GREEN;
	}
	
}

static void	advance_axis_Y(t_fdf *fdf, t_var_steep stp, t_point p1, t_point p2)
{
	t_point	s1;
	int		pos;

	stp.pk1 = 2 * stp.dx - stp.dy;
	stp.pk2 = 2 * stp.dz - stp.dy;
	while (p1.y != p2.y)
	{
		p1.y += stp.ys;
		if (stp.pk1 >= 0)
		{
			p1.x += stp.xs;
			stp.pk1 -= 2 * stp.dy;
		}
		if (stp.pk2 >= 0)
		{
			p1.z += stp.zs;
			stp.pk2 -= 2 * stp.dy;
		}
		stp.pk1 += 2 * stp.dx;
		stp.pk2 += 2 * stp.dz;
		s1 = do_isometric(p1);
		pos = (s1.y * fdf->mlx.line_bytes) + s1.x + fdf->map.offset;
		fdf->mlx.buffer[pos] = GREEN;
	}
}

static void	advance_axis_Z(t_fdf *fdf, t_var_steep stp, t_point p1, t_point p2)
{
	t_point	s1;
	int		pos;

	stp.pk1 = 2 * stp.dy - stp.dz;
	stp.pk2 = 2 * stp.dx - stp.dz;
	while (p1.z != p2.z)
	{
		p1.z += stp.zs;
		if (stp.pk1 >= 0)
		{
			p1.y += stp.ys;
			stp.pk1 -= 2 * stp.dz;
		}
		if (stp.pk2 >= 0)
		{
			p1.x += stp.xs;
			stp.pk2 -= 2 * stp.dx;
		}
		stp.pk1 += 2 * stp.dy;
		stp.pk2 += 2 * stp.dx;
		s1 = do_isometric(p1);
		pos = (s1.y * fdf->mlx.line_bytes) + s1.x + fdf->map.offset;
		fdf->mlx.buffer[pos] = GREEN;
	}
}


void	draw_steep(t_fdf *fdf, t_point p1, t_point p2)
{
	t_var_steep	stp;

	stp.dx = ft_abs(p2.x - p1.x);
	stp.dy = ft_abs(p2.y - p1.y);
	stp.dz = ft_abs(p2.z - p1.z);
	define_increase(p1, p2, &stp);
	// Axis X
	if (stp.dx >= stp.dy && stp.dx >= stp.dz)
		advance_axis_X(fdf, stp, p1, p2);
	// Axis Y
	else if (stp.dy >= stp.dx && stp.dy >= stp.dz)
		advance_axis_Y(fdf, stp, p1, p2);
	// Axis Z
	else
		advance_axis_Z(fdf, stp, p1, p2);
}

void	draw_horiz(t_fdf *fdf, t_point p1, t_point p2)
{
	int		pos;
	int		c;
	int		steep;
	t_point	screen;

	steep = p1.z != p2.z;
	if (!steep)
	{
		c = fdf->map.interval_col;
		while (c--)
		{
			screen = do_isometric(p1);
			pos = (screen.y * fdf->mlx.line_bytes) + screen.x + fdf->map.offset;
			if (p1.z == 0)
				fdf->mlx.buffer[pos] = WHITE;
			else 
				fdf->mlx.buffer[pos] = BLUE;
			p1.x++;
		}
	}
	else
		draw_steep(fdf, p1, p2);
}

void	draw_vertic(t_fdf *fdf, t_point p1, t_point p2)
{
	int		pos;
	int		c;
	int		steep;
	t_point	screen;

	steep = p1.z != p2.z;
	if (!steep)
	{
		c = fdf->map.interval_row;
		while (c--)
		{
			screen = do_isometric(p1);
			pos = (screen.y * fdf->mlx.line_bytes) + screen.x + fdf->map.offset;
			if (p1.z == 0)
				fdf->mlx.buffer[pos] = WHITE;
			else 
				fdf->mlx.buffer[pos] = BLUE;
			p1.y++;
		}
	}
	else
		draw_steep(fdf, p1, p2);
}

void	draw_win(t_fdf *fdf)
{
	t_point	p;
	t_point	px_next;
	t_point	py_next;
	int	i;
	int	j;

	i = 0;
	while (i < fdf->map.rows)
	{
		j = 0;
		fdf->p.x = 0;
		while (j < fdf->map.columns)
		{
			p = create_point(fdf->p.x, fdf->p.y, fdf->map.map[i][j]);
			if (j < fdf->map.columns - 1)
			{
				px_next = create_point(fdf->p.x + fdf->map.interval_col,
					fdf->p.y, fdf->map.map[i][j + 1]);
				draw_horiz(fdf, p, px_next);
			}
			if (i < fdf->map.rows - 1)
			{
				py_next = create_point(fdf->p.x, fdf->p.y + fdf->map.interval_row,
					fdf->map.map[i + 1][j]);
				draw_vertic(fdf, p, py_next);
			}
			fdf->p.x += fdf->map.interval_col;
			j++;
		}
		fdf->p.y += fdf->map.interval_row;
		i++;
	}
	mlx_put_image_to_window(fdf->mlx.mlx, fdf->mlx.win, fdf->mlx.img, 0, 0);
}
