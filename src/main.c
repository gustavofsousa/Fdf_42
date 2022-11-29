/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:46:51 by gusousa           #+#    #+#             */
/*   Updated: 2022/11/29 14:37:46 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	setup(t_fdf *fdf)
{
	fdf->map.rows = 0;
	fdf->map.columns = 0;
	fdf->map.interval_row = 0;
	fdf->map.interval_col = 0;
	fdf->p.x = 0;
	fdf->p.y = 0;
	fdf->p.color = ORANGE;
	fdf->mlx.win_size_x = 1200;
	fdf->mlx.win_size_y = 800;
	fdf->map.color = NULL;
	fdf->map.color_flag = 0;
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc == 2)
	{
		setup(&fdf);
		if (parse(&fdf, argv[1]))
			argc = 3;
			//if (display_mlx_win(&fdf))
				//return (1);
	}
	ft_printf("%d\t%d\t%d\n", fdf.map.columns, fdf.map.rows, fdf.map.color[0][0]);
	ft_putendl_fd("Missing arguments or invalid map", 1);
	return (0);
}
