/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:15:06 by gusousa           #+#    #+#             */
/*   Updated: 2022/09/01 17:35:11 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft_42/libft.h"
#include "./include/get_next_line_42/get_next_line.h"
#include "./mlx/mlx.h"
#include <fcntl.h>

#define W_HEIGHT 460
#define W_LENGHT 740

#define LIGHT_BLUE	0XABCDEF
#define GREEN_1		0X138D75
#define GREEN_2		0X40E0D0
#define GREEN_3		0X9FE2BF
#define GREEN_4		0XDFFF00
#define PINK		0XE94BDA

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char		*buffer;//I put int*
	int		bits_per_pixel;//32
	int		line_bytes;
	int		endian;
}	t_data;

typedef struct	s_pixel
{
	int			x;
	int			y;
	int			color;
}	t_pixel;
