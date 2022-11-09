/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 14:45:32 by gusousa           #+#    #+#             */
/*   Updated: 2022/11/09 11:04:16 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_point	create_point(int x, int y, int z)
{
	t_point	p;

	p.x = x;
	p.y = y;
	p.z = z;
	return (p);
}

static void	draw_horiz(t_fdf *fdf, t_point p1, t_point p2)
{
	int		c;
	int		steep;

	steep = p1.z != p2.z;
	if (!steep)
	{
		c = fdf->map.interval_col;
		while (c--)
		{
			please_put_my_pixel(fdf, p1);
			p1.x++;
		}
	}
	else
		draw_steep(fdf, p1, p2);
}

static void	draw_vertic(t_fdf *fdf, t_point p1, t_point p2)
{
	int		c;
	int		steep;

	steep = p1.z != p2.z;
	if (!steep)
	{
		c = fdf->map.interval_row;
		while (c--)
		{
			please_put_my_pixel(fdf, p1);
			p1.y++;
		}
	}
	else
		draw_steep(fdf, p1, p2);
}

static void	draw_the_L(t_fdf *fdf, int i, int j)
{
	t_point	p;
	t_point	px_next;
	t_point	py_next;

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
}

void	draw_win(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->map.rows)
	{
		j = 0;
		fdf->p.x = 0;
		while (j < fdf->map.columns)
		{
			draw_the_L(fdf, i, j);
			fdf->p.x += fdf->map.interval_col;
			j++;
		}
		fdf->p.y += fdf->map.interval_row;
		i++;
	}
	mlx_put_image_to_window(fdf->mlx.mlx, fdf->mlx.win, fdf->mlx.img, 0, 0);
}
