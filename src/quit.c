/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:29:32 by gusousa           #+#    #+#             */
/*   Updated: 2022/11/17 17:13:52 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	quit(t_fdf fdf)
{
	int	i;

	i = -1;
	if (fdf.map.map)
	{
		while (fdf.map.map[++i])
			free(fdf.map.map[i]);
		free(fdf.map.map);
	}


}
