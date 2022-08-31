#include "fdf.h"

int	main(void)
{
	int		fd;
	char	**map_char;
	int		**map_int;
	int		h;
	int		i;
	int		j;
	int		n_rows;
	int		n_columns;


	fd = open("./test_maps/42.fdf", O_RDONLY);
	n_rows = 0;
	while (get_next_line(fd))
			n_rows++;
	close(fd);

	map_char = malloc(n_rows * sizeof(char *));
	map_int = malloc(n_rows * sizeof(int *));

	fd = open("./test_maps/42.fdf", O_RDONLY);
	h = -1;
	while (++h < n_rows)
	{
		map_char[h] = get_next_line(fd);
		n_columns = ft_count_words_str(map_char[h], ' ');
		map_int[h] = ft_split_int(map_char[h], ' ');
		ft_putstr_fd(map_char[h], 1);
	}
	i = -1;
	while (++i < n_rows)
	{
		j = -1;
		while (++j < n_columns)
		{
			ft_putnbr_fd(map_int[i][j], 1);
		}
		ft_putstr_fd("\n", 1);
	}

	


	return (0);
}
