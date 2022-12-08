/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 11:54:53 by gusousa           #+#    #+#             */
/*   Updated: 2022/12/08 20:34:11 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	do_isometric(t_point p)
{
	double	angle;
	double	alpha;
	t_point	rtn;

	alpha = 0.0174533 * 0;
	angle = 0.0174533 * 0;
	rtn.x = p.x * cos(alpha)
		+ p.y * cos(alpha + angle)
		+ p.z * cos(alpha - angle);
	rtn.y = p.x * sin(alpha)
		+ p.y * sin(alpha + angle)
		+ p.z * sin(alpha - angle);
	return (rtn);
}

void	please_put_my_pixel(t_fdf *fdf, t_point p_in)
{
	t_point	p;
	int		pos;

	p = do_isometric(p_in);
	pos = (p.y * fdf->mlx.line_bytes) + p.x;
	// Somando um offset
	pos += (fdf->map.offset_y * fdf->mlx.line_bytes) + fdf->map.offset_x;

	// Cortando as laterais
	//if (pos < ((fdf->mlx.line_bytes * fdf->map.rows) + fdf->map.columns) - 1)
	//{
		if (fdf->map.color_flag == 1)
			fdf->mlx.buffer[pos] = fdf->map.color[fdf->map.a_row][fdf->map.a_col];
		else
		{
			if (p_in.z == 0)
				fdf->mlx.buffer[pos] = WHITE;
			else
				fdf->mlx.buffer[pos] = GREEN_3;
		}
	//}
}
