/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:29:32 by gusousa           #+#    #+#             */
/*   Updated: 2022/11/22 17:00:59 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	quit_6(t_fdf *fdf)
{
	ft_printf("./fdf <map name> [scale zscale]\n");
}

void	quit_5(t_fdf *fdf)
{
	ft_printf("found wrong line length\n");
}

void	quit_4(t_fdf *fdf)
{
	ft_printf("Found wrong line length error\n");
}

void	quit_3(t_fdf *fdf)
{
	ft_printf("No data found\n");
}

void	quit_2(t_fdf *fdf)
{
	ft_printf("Couldn't find file");
}

void	quit_1(t_fdf *fdf)
{
	int	i;

	i = -1;
	if (fdf->map.map)
	{
		while (fdf->map.map[++i])
			free(fdf->map.map[i]);
		free(fdf->map.map);
	}
	i = -1;
	if (fdf->map.map_char)
	{
		while (fdf->map.map_char[++i])
			free(fdf->map.map_char[i]);
		free(fdf->map.map_char);
	}
}

void	quit(t_fdf *fdf, int error)
{

	if (error == 1)
		quit_1(fdf);
	else if (error == 1)
		quit_2(fdf);

	exit (0);
}
