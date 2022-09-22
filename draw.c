/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 14:45:32 by gusousa           #+#    #+#             */
/*   Updated: 2022/09/22 15:32:28 by gusousa          ###   ########.fr       */
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

	alpha = 0.5236; // 30					   
	angle = 2.0944; // 120;
	rtn.x = p.x * cos(alpha)
		+ p.y * cos(alpha + angle)
		+ p.z * cos(alpha - angle);
	rtn.y = p.x * sin(alpha)
		+ p.y * sin(alpha + angle)
		+ p.z * sin(alpha - angle);
	return (rtn);
}

void	draw_steep(t_fdf *fdf, t_point p1, t_point p2)
{
	int		dx;
	int		pos;
	int		dy;
	int		pk;
	t_point	s1;
	t_point	s2;

	s1 = do_isometric(p1);
	s2 = do_isometric(p2);
	dx = s2.x - s1.x; 
	dy = s2.y - s1.y;
	pk = 2 * dy - dx;
	while (s1.x < s2.x)
	{
		s1 = do_isometric(p1);
		pos = (s1.y * fdf->mlx.line_bytes) + s1.x + 200;
		fdf->mlx.buffer[pos] = GREEN;
		if (pk >= 0)
		{
			s1.y++;
			pk += 2 * (dy - dx);
		}
		else
			pk += 2 * dy;
		s1.x++;
	}
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
			pos = (screen.y * fdf->mlx.line_bytes) + screen.x + 200;
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
			pos = (screen.y * fdf->mlx.line_bytes) + screen.x + 200;
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
	while (i < fdf->map.rows - 1)
	{
		j = 0;
		fdf->p.x = 0;
		while (j < fdf->map.columns)
		{
			p = create_point(fdf->p.x, fdf->p.y, fdf->map.map[i][j]);
			px_next = create_point(fdf->p.x + 1, fdf->p.y, fdf->map.map[i][j + 1]);
			py_next = create_point(fdf->p.x, fdf->p.y + 1, fdf->map.map[i + 1][j]);
			if (j < fdf->map.columns - 1)
				draw_horiz(fdf, p, px_next);
			if (i < fdf->map.rows - 1)
				draw_vertic(fdf, p, py_next);
			fdf->p.x += fdf->map.interval_col;
			if (p.x % fdf->map.interval_col == 0)
				j++;
		}
		fdf->p.y += fdf->map.interval_row;
		if (p.y % fdf->map.interval_row == 0)
			i++;
	}
	mlx_put_image_to_window(fdf->mlx.mlx, fdf->mlx.win, fdf->mlx.img, 0, 0);
}
