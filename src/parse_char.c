/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 15:14:52 by gusousa           #+#    #+#             */
/*   Updated: 2022/12/07 15:59:16 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	count_rows(t_fdf *fdf, char *file_name)
{
	char	*str;
	int		fd;

	fd = open(file_name, O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		fdf->map.rows++;
		free(str);
		str = get_next_line(fd);
	}
	close (fd);
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
			return (0);
	}
	fdf->map.columns = n_col;
	return (1);
}

/**
 * Usar gnl para pegar o mapa
 * Conferir se não achou dado
 */
int	get_char_map(t_fdf *fdf, int fd)
{
	int	a_row;

	a_row = -1;
	while (++a_row < fdf->map.rows)
	{
		fdf->map.map_char[a_row] = get_next_line(fd);
		if (fdf->map.map_char[0] == NULL)
		{
			ft_printf("No data found\n"); // Ou espaço.
			return (0);
		}
		else if (fdf->map.map_char[a_row] == NULL) // Ou espaço.
		{
			ft_printf("Found wrong line lenght\n");
			return (0);
		}
	}
	return (1);
}

