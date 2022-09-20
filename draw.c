/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 14:45:32 by gusousa           #+#    #+#             */
/*   Updated: 2022/09/20 19:53:23 by gusousa          ###   ########.fr       */
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

void	draw_steep(t_fdf *fdf, t_point p1, t_point p2)
{
	int	dx;
	int	pos;
	int	dy;
	int	p;
	t_point	s;

	s = do_isometric(fdf, p1.z);
	dx = p2.x - p1.x; 
	dy = p2.y - p1.y;
	p = 2 * (dy + dx);
	while (s.x < p2.x)
	{
		pos = (s.y * fdf->mlx.line_bytes) + s.x + 200;
		fdf->mlx.buffer[pos] = GREEN;
		if (p >= 0)
		{
			s.y++;
			p = p + 2 * dy - 2 * dx;
		}
		else
		{
			p = p + 2 * dy;
			s.x++;
		}
	}
}

void	draw_horiz(t_fdf *fdf, t_point p1, t_point p2)
{
	int	pos;
	int	c;
	int	steep;
	t_point	screen;
//inclinação
	steep = p1.z != p2.z;
	if (!steep)
	{
		c = fdf->map.interval_col;
		while (c--)
		{
			screen = do_isometric(fdf, p1.z);
			pos = (screen.y * fdf->mlx.line_bytes) + screen.x + 200;
			if (p1.z == 0)
				fdf->mlx.buffer[pos] = WHITE;
			else 
				fdf->mlx.buffer[pos] = BLUE;
			fdf->p.x++;
		}
		fdf->p.x -= fdf->map.interval_col;
	}
	else
		(void)c;
		//draw_steep(fdf, p1, p2);
}

void	draw_vertic(t_fdf *fdf, t_point p1, t_point p2)
{
	int	pos;
	int	c;
	int	steep;
	t_point	screen;
//inclinação
	steep = p1.z != p2.z;
	if (!steep)
	{
		c = fdf->map.interval_row;
		while (c--)
		{
			screen = do_isometric(fdf, p1.z);
			pos = (screen.y * fdf->mlx.line_bytes) + screen.x + 200;
			if (p1.z == 0)
				fdf->mlx.buffer[pos] = WHITE;
			else 
				fdf->mlx.buffer[pos] = BLUE;
			fdf->p.y++;
		}
		fdf->p.x -= fdf->map.interval_row;
	}
	else
		(void)c;
		//draw_steep(fdf, p1, p2);
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
		while (j < fdf->map.columns - 1)
		{
			p = create_point(fdf->p.x, fdf->p.y, fdf->map.map[i][j]);
			px_next = create_point(fdf->p.x + 1, fdf->p.y, fdf->map.map[i][j + 1]);
			py_next = create_point(fdf->p.x, fdf->p.y + 1, fdf->map.map[i + 1][j]);

			if (j < fdf->map.columns - 1)
				draw_horiz(fdf, p, px_next);
			if (i < fdf->map.columns - 1)
				draw_vertic(fdf, p, py_next);
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

