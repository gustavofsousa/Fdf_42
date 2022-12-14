/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:15:06 by gusousa           #+#    #+#             */
/*   Updated: 2022/12/14 15:45:43 by gusousa          ###   ########.fr       */
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

#define LIGHT_BLUE	0XABCDEF
#define GREEN_3		0X9FE2BF
#define BLUE		0x6464FF
#define WHITE		0xFFFFFF
#define RED			0xF03A15
#define REDER		0xAC270B
#define ORANGE		0xFF8000

enum e_size_img
{
	e_lenght = 1200,
	e_height = 800,
	e_tiny_lenght = 500,
	e_tiny_height = 370
};

enum	e_error_msg
{
	none,
	no_file,
	file_not_find,
	wrong_line_lenght,
	line_lenght_error,
	wrong_input,
	no_data_found,
};

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
}	t_pixel;

typedef	struct	s_map
{
	char		**map_char;
	int			**map;
	int			**color;
	int			rows;
	int			columns;
	int			interval_row;
	int			interval_col;
	int			offset_x;
	int			offset_y;
	int			color_flag;
	int			a_row;
	int			a_col;
}	t_map;

typedef struct s_fdf
{
	t_map	map;
	t_mlx	mlx;
	t_pixel	p;
	char	*file_name;
	int		fd;
	int		case_size;
	int		z_size;
	int		case_size_flag;
}	t_fdf;

//Analise
int		parse(t_fdf *fdf);

// Analise char
void	count_rows(t_fdf *fdf, char *file_name);
int		get_map_char(t_fdf *fdf);
int		count_columns(t_fdf *fdf);
//Analise int
int		turn_map_int(t_fdf *fdf);
int		get_color(t_fdf *fdf);

// MLX
int		display_mlx_win(t_fdf *fdf);
void	draw_win(t_fdf *fdf);
void	draw_steep(t_fdf *fdf, t_point p1, t_point p2);
t_point	do_isometric(t_point p);
void	please_put_my_pixel(t_fdf *fdf, t_point p_in);

void	quit(t_fdf *fdf);
void	error(t_fdf *fdf, enum e_error_msg msg);
#endif
