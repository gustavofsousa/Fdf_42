/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 11:54:53 by gusousa           #+#    #+#             */
/*   Updated: 2022/12/14 16:26:50 by gusousa          ###   ########.fr       */
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

	if (p_in.x >= 0 && p_in.x < e_lenght
			&& p_in.y >= 0 && p_in.y < e_height)
	{
		if (fdf->case_size_flag == 1)
			p_in.z *= fdf->z_size;
		p = do_isometric(p_in);
		pos = (p.y * fdf->mlx.line_bytes) + p.x;
		pos += (fdf->map.offset_y * fdf->mlx.line_bytes) + fdf->map.offset_x;
		if (fdf->map.color_flag == 1)
			fdf->mlx.buffer[pos] = fdf->map.color[fdf->map.a_row][fdf->map.a_col];
		else
		{
			if (p_in.z == 0)
				fdf->mlx.buffer[pos] = WHITE;
			else
				fdf->mlx.buffer[pos] = GREEN_3;
		}
	}
}
