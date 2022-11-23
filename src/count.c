/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 15:14:52 by gusousa           #+#    #+#             */
/*   Updated: 2022/11/23 16:57:20 by gusousa          ###   ########.fr       */
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

