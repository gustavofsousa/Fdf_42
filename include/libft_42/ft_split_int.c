/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 11:44:53 by gusousa           #+#    #+#             */
/*   Updated: 2022/08/29 15:19:36 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**split(char	**str_splitted, char const *s, char sep)
{
	size_t	qtd_words;
	size_t	line;
	size_t	word_len;

	qtd_words = ft_count_words_str(s, sep);
	line = 0;
	while (line < qtd_words)
	{
		word_len = 0;
		while (*s && (word_len == 0 || *s != sep))
		{
			if (*s != sep)
				word_len++;
			s++;
		}
		str_splitted[line] = ft_substr(s - word_len, 0, word_len);
		line++;
	}
	str_splitted[line] = 0;
	return (str_splitted);
}

int	*ft_split_int(char const *s, char c)
{
	char	**str_splitted;
	size_t	qtd_words;
	int		*int_splitted;

	if (!s)
		return (NULL);
	qtd_words = ft_count_words_str(s, c);
	str_splitted = malloc((qtd_words + 1) * sizeof(char *));
	int_splitted = malloc(qtd_words * sizeof(int));
	if (!str_splitted || !int_splitted)
		return (NULL);
	split(str_splitted, s, c);
	while (qtd_words--)
	{
		int_splitted[qtd_words] = ft_atoi(str_splitted[qtd_words]);
		free(str_splitted[qtd_words]);
	}
	free (str_splitted);
	return (int_splitted);
}
