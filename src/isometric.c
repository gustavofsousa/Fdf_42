/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 11:54:53 by gusousa           #+#    #+#             */
/*   Updated: 2022/12/17 18:23:12 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	do_isometric(t_point p)
{
	double	angle;
	double	alpha;
	t_point	rtn;

	alpha = 0.0174533 * 330;
	angle = 0.0174533 * 50;
	rtn.x = p.x * cos(alpha)
		+ p.y * cos(alpha + angle)
		+ p.z * cos(alpha - angle);
	rtn.y = p.x * sin(alpha)
		+ p.y * sin(alpha + angle)
		+ p.z * sin(alpha - angle);
	rtn.z = p.z;
	return (rtn);
}

void	please_put_my_pixel(t_fdf *fdf, t_point p)
{
	int		pos;

	p.x += fdf->map.offset_x;
	p.y += fdf->map.offset_y;
	pos = (p.y * fdf->mlx.line_bytes) + p.x;
	if (((p.x >= 0 && p.x < e_lenght)
			&& (p.y >= 0 && p.y < e_height))
		&& (pos < ((p.y + 1) * fdf->mlx.line_bytes)))
	{
		fdf->mlx.buffer[pos] = fdf->map.color[fdf->map.a_row][fdf->map.a_col];
	}
}
