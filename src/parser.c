/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 14:36:15 by gusousa           #+#    #+#             */
/*   Updated: 2022/11/21 14:42:36 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	calculate(t_fdf *fdf)
{
	fdf->map.interval_row = W_HEIGHT / fdf->map.rows;
	fdf->map.interval_col = W_LENGHT / fdf->map.columns;
	fdf->map.offset_x = fdf->mlx.win_size_x / 3;
	fdf->map.offset_y = fdf->mlx.win_size_y / 4;
}

static void	count_rows(t_fdf *fdf, char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd != -1)
	{
		while (get_next_line(fd))
			fdf->map.rows++;
		close(fd);
	}
}

static	int	count_columns(t_fdf *fdf)
{
	int	a_row;
	int	count;

	a_row = 0;
	count = ft_count_words_str(fdf->map.map_char[a_row], ' ');
	while (fdf->map.map_char[a_row])
	{
		if (count != ft_count_words_str(fdf->map.map_char[a_row++], ' '))
		{
			ft_putendl_fd("Invalid map", 1);
			return (0);
		}
		free(fdf->map.map_char[a_row]);
	}
	free(fdf->map.map_char);
	fdf->map.columns = count;
	return (1);
}

/**
 * Extrai cada linha do arquivo
 * Conta qtd_colunas
 * insere na struct mapa
 * está também pegando cor
 * e splitando
 */
int	read_map(t_fdf *fdf, char *file_name)
{
	int	fd;
	int	a_row;

	fd = open(file_name, O_RDONLY);
	if (fd != -1)
	{
		// Pegar mapa em char ** e verificar error
		// contar coluna junto.
		a_row = -1;
		while (++a_row < fdf->map.rows)
		{
			fdf->map.map_char[a_row] = get_next_line(fd);
			fdf->map.map[a_row] = ft_split_int(fdf->map.map_char[a_row], ' ');
		}
		// transformar char** em int**
		// Pegar cor depois da virgula
		// Dar free no mapa de char
		if (!count_columns(fdf))
			return (0);
		calculate(fdf);
		return (1);
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
	count_rows(fdf, file_name);
	fdf->map.map_char = malloc(fdf->map.rows * sizeof(char *));
	fdf->map.map = malloc(fdf->map.rows * sizeof(int *));
	if (fdf->map.map_char && fdf->map.map)
	{
		if (read_map(fdf, file_name))
			return (1);
	}
	else
		quit(fdf, 1);
	return (0);
}

// 1 -> desalocar mapas de entrada
