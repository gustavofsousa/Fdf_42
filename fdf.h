/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:15:06 by gusousa           #+#    #+#             */
/*   Updated: 2022/09/07 14:38:39 by gusousa          ###   ########.fr       */
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

#define BLUE		0x6464FF
#define WHITE		0xFFFFFF
#define BROWN		0x5F2B17
#define GREEN		0x36B71C
#define GREENER		0x259000

#define RED			0xF03A15
#define REDER		0xAC270B
#define ORANGE		0xFF8000
#define BROWNER		0x440D09

#define GRAY_MIN	0x4F4F4F
#define GRAY_LOW	0x6A6A6A
#define GRAY_MID	0x868686
#define GRAY_HIGH	0xC3C3C3

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	int		*buffer;
	int		bits_per_pixel;
	int		line_bytes;
	int		endian;
}	t_mlx;

typedef struct	s_pixel
{
	int			x;
	int			y;
	int			color;
}	t_pixel;

typedef	struct	s_map
{
	int	**map;
	int	rows;
	int	columns;
}	t_map;

typedef struct s_fdf
{
	t_map	map;
	t_mlx	mlx;
}	t_fdf;

int		parse(t_fdf *fdf, char *filne_name);


