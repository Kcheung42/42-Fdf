/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 16:42:31 by kcheung           #+#    #+#             */
/*   Updated: 2017/05/19 18:28:41 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		color(t_env env, int z)
{
	int		r;
	int		g;
	int		b;
	int		s;
	float	percent;

	s = env.degrees.s;
	percent = ((float)z - (float)env.z_min) /
		((float)env.z_max - (float)env.z_min) * s;
	s = env.degrees.s;
	r = 0;
	g = 255 * percent;
	b = 165;
	return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	(void)env;
	(void)z;
}

void	fdf_draw_horizontals(t_env env, t_point **plot)
{
	int	row;
	int	col;

	row = 0;
	while (plot[row])
	{
		col = 0;
		while (col < env.col_count - 1)
		{
			if (env.map[row][col] == env.map[row][col + 1])
				bresenham(plot[row][col], plot[row][col + 1],
						color(env, env.map[row][col]), env);
			else if (env.map[row][col] > env.map[row][col + 1])
				bresenham(plot[row][col], plot[row][col + 1],
						color(env, env.map[row][col + 1]), env);
			else if (env.map[row][col] < env.map[row][col + 1])
				bresenham(plot[row][col], plot[row][col + 1],
						color(env, env.map[row][col]), env);
			col++;
		}
		row++;
	}
}

void	fdf_draw_verticals(t_env env, t_point **plot)
{
	int	row;
	int	col;

	col = 0;
	row = 0;
	while (col < env.col_count)
	{
		row = 0;
		while (plot[row + 1])
		{
			if (env.map[row][col] == env.map[row + 1][col])
				bresenham(plot[row][col], plot[row + 1][col],
						color(env, env.map[row][col]), env);
			else if (env.map[row][col] > env.map[row + 1][col])
				bresenham(plot[row][col], plot[row + 1][col],
						color(env, env.map[row + 1][col]), env);
			else if (env.map[row][col] < env.map[row + 1][col])
				bresenham(plot[row][col], plot[row + 1][col],
						color(env, env.map[row][col]), env);
			row++;
		}
		col++;
	}
}

void	fdf_display(t_env env, t_point **plot)
{
	fdf_draw_verticals(env, plot);
	fdf_draw_horizontals(env, plot);
	(void)env;
}
