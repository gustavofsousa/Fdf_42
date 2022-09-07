/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 14:36:15 by gusousa           #+#    #+#             */
/*   Updated: 2022/09/07 15:07:31 by gusousa          ###   ########.fr       */
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
				//Check for invalid map
				map_char[a_row] = get_next_line(fd);
				fdf->map.map[a_row] = ft_split_int(map_char[a_row], ' ');
				fdf->map.columns = (int)ft_count_words_str(map_char[a_row], ' ');
				free(map_char[a_row]);
			}
			free(map_char);
			return (1);
		}
	}
	return (0);
}
