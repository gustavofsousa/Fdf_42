/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 14:36:15 by gusousa           #+#    #+#             */
/*   Updated: 2022/12/06 19:03:56 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	calculate(t_fdf *fdf)
{
	fdf->map.interval_row = W_HEIGHT / fdf->map.rows;
	fdf->map.interval_col = W_LENGHT / fdf->map.columns;
	fdf->map.offset_x = fdf->mlx.win_size_x / 3;
	fdf->map.offset_y = fdf->mlx.win_size_y / 4;
}

int    ft_atohex(char *str)
{
	static int    hex_values[6] = {10, 11, 12, 13, 14, 15};
	int            nbr;
	int            i;

	if (!str)
		return (0);
	nbr = 0;
	i = 0;
	if (ft_strncmp(str, ",0x", 3) == 0 || ft_strncmp(str, ",0X", 3) == 0)
		i += 3;
	while (str[i] != '\0' && str[i] != ' ')
	{
		if (ft_isdigit(str[i]))
			nbr = nbr * 16 + (str[i] - 48);
		else if (str[i] >= 'a' && str[i] <= 'f')
			nbr = nbr * 16 + hex_values[(str[i] - 97)];
		else if (str[i] >= 'A' && str[i] <= 'F')
			nbr = nbr * 16 + hex_values[(str[i] - 65)];
		i++;
	}
	return (nbr);
}

/*
int	ft_atohex(char *str, int len)
{
	int	nbr;
	int	i;
	char	*base;
	int		pre;

	i = 0;
	if (str[i + 1] == 'X')
		i += 2;
	base = "0123456789ABCDEF";
	while (len--)
	{
		pre = str[i++] - '0';
		nbr = nbr * 10 + base[pre % 16];
	}
	return (nbr);
}
*/

/**
 *	ir até o fim da virgula
 *	Receber com atoHEX
 */
void	extract(t_fdf *fdf, int a_row)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (fdf->map.map_char[a_row][i])
	{
		if (fdf->map.map_char[a_row][i] == ',')
		{
			fdf->map.color[a_row][c] = ft_atohex((fdf->map).map_char[a_row] + i);
			c++;
		}
		i++;
	}

}

// Verificar na primeira linha se tem ','
// Capturar cada valor depois da linha e guardar na struct.
int	get_color(t_fdf *fdf)
{
	int	a_row;


	if (ft_strchr(fdf->map.map_char[0], ','))
	{
		fdf->map.color_flag = 1;
		fdf->map.color = malloc(fdf->map.rows * sizeof(int *));
		if (fdf->map.color)
		{
			a_row = -1;
			while (++a_row < fdf->map.rows)
			{
					fdf->map.color[a_row] = malloc(fdf->map.rows * sizeof(int));
					if (fdf->map.color[a_row])
						extract(fdf, a_row);
					else
						return (0);
			}
		}
		else
			return (0);
	}
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
		if (fdf->map.map_char[a_row])
		{
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
		else
			return (0);
	}
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

	fd = open(file_name, O_RDONLY);
	if (fd != -1)
	{
		if (get_char_map(fdf, fd))
		{
			if (count_columns(fdf))
			{
				if (turn_map_int(fdf))
				{
					if (get_color(fdf))
					{
						calculate(fdf);
						close(fd);
						return (1);
					}
					else
						quit(fdf, 8); // Erro malloc color
				}
				else
					quit(fdf, 7); //Erro malloc int_map
			}
			else
				quit(fdf, 4); //Wrong line lenght error
		}
		else
			quit(fdf, 3); // No data found. Wrong line lenght. Erro malloc char_map.
	}
	close(fd);
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
	if (fdf->map.map_char)
	{
		if (read_map(fdf, file_name))
			return (1);
	}
	else
		quit(fdf, 1); // Error malloc map_char incompleto
	return (0);
}

// 1 -> Proteção do maloc dos mapas. desalocar mapas de entrada.
// 2 -> "couldn't find a file"
