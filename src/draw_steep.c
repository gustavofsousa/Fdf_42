/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_steep.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 11:32:29 by gusousa           #+#    #+#             */
/*   Updated: 2022/09/28 11:32:54 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
