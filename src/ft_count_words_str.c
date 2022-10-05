/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 15:14:52 by gusousa           #+#    #+#             */
/*   Updated: 2022/08/29 16:06:06 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_count_words_str(char const *s, char sep)
{
	size_t	i;
	size_t	qtd_word;
	size_t	next;

	i = 0;
	qtd_word = 0;
	while (s[i])
	{
		next = i + 1;
		if (s[i] != sep && (s[next] == sep || s[next] == '\0'))
			qtd_word++;
		i++;
	}
	return (qtd_word);
}
