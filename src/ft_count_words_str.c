/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 15:14:52 by gusousa           #+#    #+#             */
/*   Updated: 2022/11/23 15:57:02 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_words(char *str)
{
	int	i;
	int	qtd_word;

	i = 0;
	qtd_word = 1;
	while (str[i + 1])
	{
		if (str[i] != " " && str[i + 1] == " ")
			qtd_word++;
		i++;
	}
	return (qtd_word);
}

int	count_columns(t_fdf *fdf)
{
	int	n_col;

	n_col = count_words(fdf->map.map_char[0])
}
