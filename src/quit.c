/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:29:32 by gusousa           #+#    #+#             */
/*   Updated: 2022/12/13 19:53:12 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	extinguish_mlx(t_fdf *fdf)
{
	if (fdf->mlx.win)
		mlx_destroy_window(fdf->mlx.mlx, fdf->mlx.win);
	if (fdf->mlx.img)
		mlx_destroy_image(fdf->mlx.mlx, fdf->mlx.img);
}

void	extinguish_maps(t_fdf *fdf)
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
	i = -1;
	if (fdf->map.color)
	{
		while (fdf->map.color[++i])
			free(fdf->map.color[i]);
		free(fdf->map.color);
	}
}

void	quit(t_fdf *fdf)
{
	extinguish_maps(fdf);
	extinguish_mlx(fdf);
	free(fdf->file_name);
	if (fdf->fd > 2)
		close(fdf->fd);
	exit (0);
}

void	error(t_fdf *fdf, enum e_error_msg msg)
{
	if (msg == no_file) //quit_2
		ft_printf("No file %s\n", fdf->file_name);
	else if (msg == file_not_find) //
		ft_printf("Couldn't find file");
	else if (msg == wrong_line_lenght)
		ft_printf("found wrong line lenght. Exiting.\n");
	else if (msg == line_lenght_error) //quit_1
		ft_printf("Found wrong line lenght error.\n");
	else if (msg == wrong_input)
		ft_printf("./fdf <map name> [scale zscale]\n");
	else if (msg == no_data_found)//quit_3
		ft_printf("No data found.\n");
	quit(fdf);
}
