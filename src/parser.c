/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 14:36:15 by gusousa           #+#    #+#             */
/*   Updated: 2022/12/08 16:07:10 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	calculate(t_fdf *fdf)
{ // Inverti leinght height com o debaixo
	fdf->map.interval_row = e_tiny_lenght / fdf->map.rows;
	fdf->map.interval_col = e_tiny_height / fdf->map.columns;
	fdf->map.offset_x = e_lenght / 3;
	fdf->map.offset_y = e_height / 4;
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

int	parse_map_char(t_fdf *fdf, int fd, char *file_name)
{
	count_rows(fdf, file_name);
	fdf->map.map_char = malloc(fdf->map.rows * sizeof(char *));
	if (fdf->map.map_char)
	{
		if (get_char_map(fdf, fd))
		{
			close(fd);
			if (count_columns(fdf))
				return (1);
			else
				quit(fdf, 4); //Wrong line lenght error
		}
		else
		{
			close (fd);
			quit(fdf, 3); // No data found. Wrong line lenght. Erro malloc char_map.
		}
	}
	else
	{
		close (fd);
		quit(fdf, 1); // Error malloc map_char incompleto
	}
	return (0);
}

/**
 * Receber o mapa com gnl
 * Colocar em char **
 * Converter para int **
 * Verificar se é um mapa válido
 * Guardar as cores
 */
int	parse(t_fdf *fdf, char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd != -1)
	{
		if (parse_map_char(fdf, fd, file_name))
		{
			if (parse_map_int(fdf))
			{
				calculate(fdf);
				return (1);
			}
		}
	}
	else
	{
		ft_printf("No file %s\n", file_name);
		quit(fdf, 2); // Couldn't find file. // Nada de malloc
	}
	return (0);
}
