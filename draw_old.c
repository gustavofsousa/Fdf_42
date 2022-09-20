/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 14:45:32 by gusousa           #+#    #+#             */
/*   Updated: 2022/09/20 15:37:50 by gusousa          ###   ########.fr       */
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
/*
void	do_isometric(t_fdf *fdf, int c, int z)
{
	// Função que calcula a posição
	// Esccolher entre adicionar o c no y ou x
	// Adicionar e fazer a conta isométrico.
	// retornar.
	
	double	angle = 2.0944;// 120;
	double	alpha = 0.5236;// 30
	double	u;
	double	v;
	int		x;
	int		y;
	int		z;
		
	y = fdf->p.y;
	x = fdf->p.x;
	z = p.z;//Falta trazer esse z

	if (horiz)
		x = fdf->p.x + c;
	if (vertic)
		y = fdf->p.y + c;
	u = x * cos(alpha) + y * cos(alpha + angle) + fdf->map.z * cos(alpha - angle);
	v = x * sen(alpha) + y * sen(alpha + angle) + fdf->map.z * sen(alpha - angle);
}*/

t_pixel	do_isometric(int width, int height, int x, int y)
{
	t_pixel rtn;

	rtn.x = (x / width) + (y /height);
	rtn.y = (y / height) - (x / width);
	return (rtn);
}

void	draw_horiz(t_fdf *fdf, t_point p1, t_point p2)
{
	int	pos;
	int	c;
	int	x;
	t_pixel	screen;

	c = 0;
	while (c < fdf->map.interval_col)
	{
		x = fdf->p.x + c;
		screen = do_isometric(p2.x - p1.x, p2.y - p1.y, x, fdf->p.y);
		pos = (screen.y * fdf->mlx.line_bytes) + screen.x;
		if (p1.z - p2.z == 0)
			if (p1.z == 0)
				fdf->mlx.buffer[pos] = WHITE;
			else 
				fdf->mlx.buffer[pos] = BLUE;
		else
			fdf->mlx.buffer[pos] = GREEN;
		c++;
	}
}

void	draw_vertic(t_fdf *fdf, t_point p1, t_point p2)
{
	int	pos;
	int	c;

	c = 0;
	while (c < fdf->map.interval_row)
	{
		pos = ((fdf->p.y + c) * fdf->mlx.line_bytes) + fdf->p.x;
		if (p1.z - p2.z == 0)
			if (p1.z == 0)
				fdf->mlx.buffer[pos] = WHITE;
			else
				fdf->mlx.buffer[pos] = BLUE;
		else
			fdf->mlx.buffer[pos] = GREEN;
		c++;
	}
}

// Colocar a mesma função, diferenciar só a pos
// Fazer struct com ponto. x y z.
// Ao mudar a pos, já fazer multiplicar pelo resultado do isometric.


t_point	create_point(int x, int y, int z)
{
	t_point	p;
	p.x = x;
	p.y = y;
	p.z = z;
	return (p);
}
void	draw_win(t_fdf *fdf)
{
	t_point	p;
	t_point	px_next;
	t_point	py_next;
	int	i;
	int	j;

// 






	i = 0;
	while (i < fdf->map.rows - 1)
	{
		j = 0;
		fdf->p.x = 0;
		while (j < fdf->map.columns - 1)
		{
			p = create_point(i, j,  fdf->map.map[i][j]);
			px_next = create_point(i, j,  fdf->map.map[i][j + 1]);
			py_next = create_point(i, j,  fdf->map.map[i + 1][j]);
			if (j < fdf->map.columns - 1)
				draw_horiz(fdf, p, px_next);
			if (i < fdf->map.columns - 1)
				draw_vertic(fdf, p, py_next);
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

