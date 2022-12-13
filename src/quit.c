/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:29:32 by gusousa           #+#    #+#             */
/*   Updated: 2022/12/13 15:01:17 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

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
	/*
	i = -1;
	if (fdf->map.map_char)
	{
		while (fdf->map.map_char[++i])
			free(fdf->map.map_char[i]);
		free(fdf->map.map_char);
	}
	*/
	i = -1;
	if (fdf->map.color)
	{
		while (fdf->map.color[++i])
			free(fdf->map.color[i]);
		free(fdf->map.color);
	}
	free(fdf->file_name);
	if (fdf->fd > 2)
		close(fdf->fd);
}

void	quit_6(t_fdf *fdf)
{
	(void)fdf;
}

void	quit_5(t_fdf *fdf)
{
	ft_printf("found wrong line length. Exiting.\n");
	// Limpar o char_map incompleto.
	(void)fdf;
}

void	quit_4(t_fdf *fdf)
{
	ft_printf("Found wrong line length error\n");
	// Limpar o char_map completo
	quit_1(fdf);
}

void	quit_3(t_fdf *fdf)
{
	// Limpar char_map incompleto.
	quit_1(fdf);
}

void	quit_2(t_fdf *fdf)
{
	ft_printf("Couldn't find file");
	(void)fdf;
}

void	quit_7(t_fdf *fdf)
{
	ft_printf("error malloc int");
	(void)fdf;
	// Limpar int_map incompleto
	// Limpar char_map completo.
}


void	quit(t_fdf *fdf, int error)
{

	if (error == 1)
		quit_1(fdf);
	else if (error == 1)
		quit_2(fdf);
	else if (error == 3)
		quit_3(fdf);
	else if (error == 4)
		quit_4(fdf);
	else if (error == 5)
		quit_5(fdf);
	else if (error == 6)
		quit_6(fdf);

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

}
