/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 14:36:15 by gusousa           #+#    #+#             */
/*   Updated: 2022/09/07 18:57:06 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	count_rows(t_fdf *fdf, char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	while (get_next_line(fd))
		fdf->map.rows++;
	close(fd);
}

static	void	count_columns(t_fdf *fdf, char **map_char)
{
	int	a_row;
	int	count;

	a_row = 0;
	count = (int)ft_count_words_str(map_char[a_row], ' ');
	while (map_char[a_row])
		if (count != (int)ft_count_words_str(map_char[a_row++], ' '))
		{
			ft_putendl_fd("Invalid map", 1);
			exit (0);
		}
	fdf->map.columns = count;
}

void	dub_free(char **mat)
{
	int	row;

	row = -1;
	while (mat[++row])
		free(mat[row]);
	free(mat);
}


int	parse(t_fdf *fdf, char *file_name)
{
	char	**map_char;
	int		a_row;
	int		fd;

	count_rows(fdf, file_name);
	map_char = 0;
	map_char = malloc(fdf->map.rows * sizeof(char *));
	if (map_char != 0)
	{
		fdf->map.map = malloc(fdf->map.rows * sizeof(int *));
		if (fdf->map.map != 0)
		{
			fd = open(file_name, O_RDONLY);
			a_row = -1;
			while (++a_row < fdf->map.rows)
			{
				map_char[a_row] = get_next_line(fd);
				fdf->map.map[a_row] = ft_split_int(map_char[a_row], ' ');
				free(map_char[a_row]);
			}
			free(map_char);
			fdf->map.interval_row = W_HEIGHT / fdf->map.rows;
			fdf->map.interval_col = W_LENGHT / fdf->map.columns;
			return (1);
		}
	}
	return (0);
}
