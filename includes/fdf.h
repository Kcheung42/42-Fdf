/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 22:36:51 by kcheung           #+#    #+#             */
/*   Updated: 2017/05/19 18:38:07 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "mlx.h"
# include "libft.h"

# define ROW_SIZE 1
# define COL_SIZE 1
#define abs(v) ((v) < 0 ? -(v) : (v))
# define BLUE 0x0000ff
# define RED 0xff0000
# define YEL 0xffff00
# define WHT 0xffffff

#include "libft.h"

typedef struct	s_win
{
	void		*mlx;
	void		*win;
	void		*img;
	int			count;

}	t_win;

typedef struct	s_point
{
	int	x;
	int	y;
	int	z;
	int	s;
}				t_point;

typedef struct	s_rot
{
	int			x;
	int			y;
	int			z;
	int			s;
}				t_rot;

typedef struct	s_env
{
	t_win		*window;
	int			**map;
	t_point		**cart_points;
	int			row_count;
	int			col_count;
	int			screen_width;
	int			screen_height;
	int			spacing;
	int			z_min;
	int			z_max;
	t_rot		degrees;
}				t_env;

typedef struct s_bres
{
	double	x1;
	double	y1;
	double	x2;
	double	y2;
	double	y;
	double	x;
	double	rise;
	double	run;
	double	m;
	double	delta;
	double	adjust;
	double	threshold;
	double	offset;
	double	tmpx;
	float	tmpy;
	int		thresholdInc;
	float		offsetx;
	float		offsety;
}				t_bres;

int		color(t_env env, int z);
void	fdf_draw_horizontals(t_env env, t_point **plot);
void	fdf_draw_verticals(t_env env, t_point **plot);
void	fdf_display(t_env env, t_point **plot);
t_point	**malloc_matrix(t_env env);
void	rotate_x(int *a_y, int *a_z, int theta);
void	rotate_y(int *a_x, int *a_z, int theta);
void	rotate_z(int *a_x, int *a_y, int theta);
t_point	**update(t_env env);
void	run_over_rise(t_bres vars, t_win *window, int color);
void	rise_over_run(t_bres vars, t_win *window, int color);
void	vertical_line(t_bres vars, t_win *window, int color);
void	bresenham(t_point pt_a, t_point pt_b, int color, t_env env);
float	calc_pixel_size(t_env env);
void	resize_row(t_env *env);
void	resize_col(t_env *env, int row);
void	validate_assign(t_env *env, char *str, int row, int col);
void	ft_getmap(t_env *env, int fd);
t_point	**get_plot(t_env env, int **array);
void	print_points(t_env env, t_point **plot);
void	init_env(t_env *env, char **argv);
int		mouse_hook(int button, int x, int y, t_env *env);
void	free_matrix(t_point **matrix);
void	redraw(t_env *env);
int		my_key_func(int keycode, t_env *env);
void	scale_z(double adjust, t_env env);
void	iso_convert(double theta, t_env env);
t_point	**extrude(t_env env);
int		expose_redraw(t_env *env);
void	convert_to_screen(t_point **plot, t_env env);

#endif
