/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 15:14:52 by gusousa           #+#    #+#             */
/*   Updated: 2022/11/23 18:23:32 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	count_rows(t_fdf *fdf, char *file_name)
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

// Conta a quantidade de palavras na linha.
int	count_words(char *str)
{
	int	i;
	int	qtd_word;

	i = 0;
	qtd_word = 1;
	while (str[i + 1])
	{
		if (str[i] != ' ' && str[i + 1] == ' ')
			qtd_word++;
		i++;
	}
	return (qtd_word);
}

/**
 * Conta quantidade da 1ª linha.
 * Confere as outras linhas são menores.
 */
int	count_columns(t_fdf *fdf)
{
	int	n_col;
	int	a_row;

	n_col = count_words(fdf->map.map_char[0]);
	a_row = -1;
	while (++a_row < fdf->map.rows)
	{
		if (count_words(fdf->map.map_char[a_row]) < n_col)
		{
			quit(fdf, 4);
			return (0);
		}
	}
	fdf->map.columns = n_col;
	return (1);
}

/**
 * Divido o meu map_char com split.
 * Faço a transposta para o map_int.
 * Dou free na split.
 */
void	transpose(t_fdf *fdf, int a_row)
{
	int	i;
	char	**str;

	i = fdf->map.columns;
	while (i--)
	{
		str = ft_split(fdf->map.map_char[a_row], ' ');
		fdf->map.map[a_row][i] = ft_atoi(str[i]);
		free(str[i]);
	}
	free(str);
}

/**
 * Devo dividir as minhas linhas
 * Colocar cada linha como numeros do meuint
 * dar free no split.
 */
int	turn_map_int(t_fdf *fdf)
{
	int	a_row;

	fdf->map.map = malloc(fdf->map.rows * sizeof(int *));
	if (fdf->map.map)
	{
		a_row= -1;
		while (++a_row < fdf->map.rows)
		{
			fdf->map.map[a_row] = malloc(fdf->map.columns * sizeof(int));
			if (fdf->map.map[a_row])
				transpose(fdf, a_row);
			else
				return (0);
		}
	}
	else
		return (0);
	return (1);
}
