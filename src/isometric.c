/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 11:54:53 by gusousa           #+#    #+#             */
/*   Updated: 2022/12/14 18:18:53 by gusousa          ###   ########.fr       */
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
	return (rtn);
}

void	please_put_my_pixel(t_fdf *fdf, t_point p_in)
{
	t_point	p;
	int		pos;
	int		color;

	if (fdf->case_size_flag == 1)
		p_in.z *= fdf->z_size;

	p = do_isometric(p_in);

	pos = (p.y * fdf->mlx.line_bytes) + p.x;
	pos += (fdf->map.offset_y * fdf->mlx.line_bytes) + fdf->map.offset_x;

	if (pos < (p_in.y + 2) * fdf->mlx.line_bytes)
	{
		if (fdf->map.color_flag == 1)
		{
			color = fdf->map.color[fdf->map.a_row][fdf->map.a_col];
			fdf->mlx.buffer[pos] = color;
		}
		else
		{
			if (p_in.z == 0)
				fdf->mlx.buffer[pos] = WHITE;
			else
				fdf->mlx.buffer[pos] = GREEN_3;
		}
	}
}
