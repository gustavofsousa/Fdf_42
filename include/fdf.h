/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:15:06 by gusousa           #+#    #+#             */
/*   Updated: 2022/12/06 19:39:51 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "../libft/libft.h"
# include "./get_next_line.h"
# include "../miniLibX/mlx.h"
# include "../ft_printf/ft_printf.h"
#include <fcntl.h>
#include <math.h>

#define W_HEIGHT 400
#define W_LENGHT 270

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
	int		win_size_x;
	int		win_size_y;
}	t_mlx;

typedef struct	s_point
{
	int	x;
	int	y;
	int	z;
}	t_point;

typedef struct	s_var_steep
{
	int dx;
	int	dy;
	int	dz;
	int	xs;
	int	ys;
	int	zs;
	int	pk1;
	int	pk2;
}	t_var_steep;

typedef struct	s_pixel
{
	int			x;
	int			y;
	int			color;
}	t_pixel;

typedef	struct	s_map
{
	int			**map;
	char		**map_char;
	int			rows;
	int			columns;
	int			interval_row;
	int			interval_col;
	int			offset_x;
	int			offset_y;
	int		**color;
	int		color_flag;
}	t_map;

typedef struct s_fdf
{
	t_map	map;
	t_mlx	mlx;
	t_pixel	p;
}	t_fdf;

//Analise
int		parse(t_fdf *fdf, char *file_name);

// Analise char
int		count_columns(t_fdf *fdf);
void	count_rows(t_fdf *fdf, int fd);
//Analise int
int		turn_map_int(t_fdf *fdf);

// MLX
int		display_mlx_win(t_fdf *fdf);
void	draw_win(t_fdf *fdf);
void	draw_steep(t_fdf *fdf, t_point p1, t_point p2);
t_point	do_isometric(t_point p);
void	please_put_my_pixel(t_fdf *fdf, t_point p_in);

void	quit(t_fdf *fdf, int error);
#endif
