/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 14:36:15 by gusousa           #+#    #+#             */
/*   Updated: 2022/12/13 16:08:20 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	calculate(t_fdf *fdf)
{
	fdf->map.interval_row = e_tiny_height / fdf->map.rows;
	fdf->map.interval_col = e_tiny_lenght / fdf->map.columns;
	fdf->map.offset_x = e_lenght / 4;
	fdf->map.offset_y = e_height / 2;
}

/**
 * Extrai cada linha do arquivo
 * Conta qtd_colunas
 * insere na struct mapa
 * está também pegando cor
 * e splitando
 */
int	parse_map_int(t_fdf *fdf)
{
	if (turn_map_int(fdf))
	{
		if (get_color(fdf))
			return (1);
		else
			quit(fdf, 8); // Erro malloc color
	}
	else
		quit(fdf, 7); //Erro malloc int_map
	return (0);
}

int	parse_map_char(t_fdf *fdf, char *file_name)
{
	count_rows(fdf, file_name);
	fdf->map.map_char = malloc(fdf->map.rows * sizeof(char *));
	if (fdf->map.map_char)
		if (get_map_char(fdf))
			if (count_columns(fdf))
				return (1);
	return (0);
}

/**
 * Receber o mapa com gnl
 * Colocar em char **
 * Converter para int **
 */
int	parse(t_fdf *fdf, char *file_name)
{
	fdf->fd = open(file_name, O_RDONLY);
	if (fdf->fd != -1)
	{
		if (parse_map_char(fdf, file_name))
		{
			if (parse_map_int(fdf))
			{
				calculate(fdf);
				return (1);
			}
		}
	}
	else
		error(fdf, no_file);
	return (0);
}
