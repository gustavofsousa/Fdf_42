/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 19:45:44 by gusousa           #+#    #+#             */
/*   Updated: 2022/12/06 19:50:55 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

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
 * Divido o meu map_char com split.
 * Faço a transposta para o map_int.
 * Dou free na split.
 */
void	transpose(t_fdf *fdf, int a_row)
{
	int	i;
	char	**str;

	str = ft_split(fdf->map.map_char[a_row], ' ');
	i = 0;
	while (i < fdf->map.columns)
	{
		fdf->map.map[a_row][i] = ft_atoi(str[i]);
		free(str[i]);
		i++;
	}
	free(str[i]);
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
		a_row = -1;
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
