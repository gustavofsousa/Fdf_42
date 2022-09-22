/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 14:36:15 by gusousa           #+#    #+#             */
/*   Updated: 2022/09/22 18:24:00 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	calculate(t_fdf *fdf)
{
	int	h_img;

	fdf->map.interval_row = W_HEIGHT / fdf->map.rows;
	fdf->map.interval_col = W_LENGHT / fdf->map.columns;
	h_img = fdf->map.interval_row * fdf->map.rows;
	//fdf->map.offset = cos(0.0174533 * 30) * h_img;
	fdf->map.offset = 100;
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

static	int	count_columns(t_fdf *fdf, char **map_char)
{
	int	a_row;
	int	count;

	a_row = 0;
	count = (int)ft_count_words_str(map_char[a_row], ' ');
	while (map_char[a_row])
	{
		if (count != (int)ft_count_words_str(map_char[a_row++], ' '))
		{
			ft_putendl_fd("Invalid map", 1);
			return (0);
		}
		free(map_char[a_row]);
	}
	free(map_char);
	fdf->map.columns = count;
	return (1);
}

int	read_map(t_fdf *fdf, char *file_name, char **map_char)
{
	int	fd;
	int	a_row;

	fd = open(file_name, O_RDONLY);
	if (fd != -1)
	{
		a_row = -1;
		while (++a_row < fdf->map.rows)
		{
			map_char[a_row] = get_next_line(fd);
			fdf->map.map[a_row] = ft_split_int(map_char[a_row], ' ');
		}
		if (!count_columns(fdf, map_char))
			return (0);
		calculate(fdf);
		return (1);
	}
	return (0);
}

int	parse(t_fdf *fdf, char *file_name)
{
	char	**map_char;

	count_rows(fdf, file_name);
	map_char = 0;
	map_char = malloc(fdf->map.rows * sizeof(char *));
	if (map_char != 0)
	{
		fdf->map.map = malloc(fdf->map.rows * sizeof(int *));
		if (fdf->map.map != 0)
			if (read_map(fdf, file_name, map_char))
				return (1);
	}
	return (0);
}
