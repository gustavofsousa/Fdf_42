/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:46:51 by gusousa           #+#    #+#             */
/*   Updated: 2022/12/14 16:24:54 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_case_size(t_fdf *fdf, char **argv)
{
	fdf->case_size = ft_atoi(argv[2]);
	fdf->z_size = ft_atoi(argv[3]);
	if (fdf->case_size == 0 || fdf->z_size == 0)
	{
		fdf->case_size = 1;
		fdf->z_size = 1;
	}
}

void	setup(t_fdf *fdf, int argc, char **argv)
{
	if (argc == 4)
	{
		fdf->case_size_flag = 1;
		get_case_size(fdf, argv);
	}
	fdf->file_name = ft_strdup(argv[1]);
	fdf->map.rows = 0;
	fdf->map.columns = 0;
	fdf->map.interval_row = 0;
	fdf->map.interval_col = 0;
	fdf->p.x = 0;
	fdf->p.y = 0;
	fdf->map.color = NULL;
	fdf->map.map = NULL;
	fdf->map.map_char = NULL;
	fdf->map.color_flag = 0;
	fdf->mlx.win = NULL;
	fdf->mlx.img = NULL;
	fdf->fd = 0;
	fdf->case_size_flag = 0;
	fdf->case_size = 1;
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc == 2 || argc == 4)
	{
		setup(&fdf, argc, argv);
		if (parse(&fdf))
			if (display_mlx_win(&fdf))
				return (0);
		quit(&fdf);
	}
	else
		ft_printf("Usage : %s <filename> [ case_size z_size ]\n", argv[0]);
	return (0);
}
