/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 16:43:50 by kcheung           #+#    #+#             */
/*   Updated: 2018/01/30 21:06:13 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x(int *a_y, int *a_z, int theta)
{
	int		y;
	int		z;
	double	radians;

	y = *a_y;
	z = *a_z;
	radians = theta * M_PI / 180;
	*a_y = y * cos(radians) - z * sin(radians);
	*a_z = y * sin(radians) + z * cos(radians);
}

void	rotate_y(int *a_x, int *a_z, int theta)
{
	int		x;
	int		z;
	double	radians;

	x = *a_x;
	z = *a_z;
	radians = theta * M_PI / 180;
	*a_x = x * cos(radians) + z * sin(radians);
	*a_z = x * -sin(radians) + z * cos(radians);
}

void	rotate_z(int *a_x, int *a_y, int theta)
{
	int		x;
	int		y;
	double	radians;

	x = *a_x;
	y = *a_y;
	radians = theta * M_PI / 180;
	*a_x = x * cos(radians) - y * sin(radians);
	*a_y = x * sin(radians) + y * cos(radians);
}

t_point	**update(t_env env)
{
	int			row;
	int			col;
	t_point		**m;

	row = 0;
	m = malloc_matrix(env);
	while (env.cart_points[row])
	{
		col = 0;
		while (col < env.col_count)
		{
			m[row][col].x = env.cart_points[row][col].x;
			m[row][col].y = env.cart_points[row][col].y;
			m[row][col].z = env.cart_points[row][col].z * env.degrees.s;
			rotate_x(&m[row][col].y, &m[row][col].z, env.degrees.x);
			rotate_y(&m[row][col].x, &m[row][col].z, env.degrees.y);
			rotate_z(&m[row][col].x, &m[row][col].y, env.degrees.z);
			col++;
		}
		row++;
	}
	m[row] = NULL;
	return (m);
}
