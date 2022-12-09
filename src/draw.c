/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 14:45:32 by gusousa           #+#    #+#             */
/*   Updated: 2022/12/09 10:24:05 by gusousa          ###   ########.fr       */
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

static void	draw_straight(t_fdf *fdf, t_point p1, char a, int interval)
{
	while (interval--)
	{
		please_put_my_pixel(fdf, p1);
		if (a == 'x')
			p1.x++;
		else if (a == 'y')
			p1.y++;
	}
}

static void	draw_line(t_fdf *fdf, t_point p1, t_point p2)
{
	if (p1.z != p2.z) // inclinado
		draw_steep(fdf, p1, p2);
	else if (p1.y == p2.y) // Na mesma coluna
		draw_straight(fdf, p1, 'x', fdf->map.interval_col);
	else if (p1.x == p2.x) // Na mesma linha
		draw_straight(fdf, p1, 'y', fdf->map.interval_row);
}

/*
 *	Desenho entre o ponto atual e o próximo, no x e y.
 */
static void	draw_the_l(t_fdf *fdf, int i, int j)
{
	t_point	p;
	t_point	px_next;
	t_point	py_next;

	p = create_point(fdf->p.x, fdf->p.y, fdf->map.map[i][j]);
	if (j < fdf->map.columns - 1)
	{
		px_next = create_point(fdf->p.x + fdf->map.interval_col,
				fdf->p.y, fdf->map.map[i][j + 1]);
		draw_line(fdf, p, px_next);
	}
	if (i < fdf->map.rows - 1)
	{
		py_next = create_point(fdf->p.x, fdf->p.y + fdf->map.interval_row,
				fdf->map.map[i + 1][j]);
		draw_line(fdf, p, py_next);
	}
}

/**
 *	Ando em cada pixel da imagem para desenhar
 */
void	draw_win(t_fdf *fdf)
{
	fdf->map.a_row = 0;
	while (fdf->map.a_row < fdf->map.rows)
	{
		fdf->map.a_col = 0;
		fdf->p.x = 0;
		while (fdf->map.a_col < fdf->map.columns)
		{
			draw_the_l(fdf, fdf->map.a_row, fdf->map.a_col);
			fdf->p.x += fdf->map.interval_col;
			fdf->map.a_col++;
		}
		fdf->p.y += fdf->map.interval_row;
		fdf->map.a_row++;
	}
	mlx_put_image_to_window(fdf->mlx.mlx, fdf->mlx.win, fdf->mlx.img, 0, 0);
}
