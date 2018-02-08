/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 16:49:14 by kcheung           #+#    #+#             */
/*   Updated: 2018/02/02 17:34:03 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	run_over_rise(t_bres vars, t_win *window, int color)
{
	vars.delta = abs(vars.rise) * 2;
	vars.threshold = abs(vars.run);
	vars.thresholdInc = abs(vars.run) * 2;
	vars.y = vars.y1;
	if (vars.x2 < vars.x1)
	{
		vars.tmpx = vars.x1;
		vars.x1 = vars.x2;
		vars.x2 = vars.tmpx;
		vars.y = vars.y2;
	}
	vars.x = vars.x1;
	while (vars.x <= vars.x2)
	{
		mlx_pixel_put(window->mlx, window->win, vars.x, vars.y, 0);
		mlx_pixel_put(window->mlx, window->win, vars.x, vars.y, color);
		vars.offset += vars.delta;
		if (vars.offset >= vars.threshold)
		{
			vars.y += vars.adjust;
			vars.threshold += vars.thresholdInc;
		}
		vars.x++;
	}
}

void	rise_over_run(t_bres vars, t_win *window, int color)
{
	vars.delta = abs(vars.run) * 2;
	vars.threshold = abs(vars.rise);
	vars.thresholdInc = abs(vars.rise) * 2;
	vars.x = vars.x1;
	if (vars.y2 < vars.y1)
	{
		vars.tmpy = vars.y1;
		vars.y1 = vars.y2;
		vars.y2 = vars.tmpy;
		vars.x = vars.x2;
	}
	vars.y = vars.y1;
	while (vars.y < vars.y2 + 1)
	{
		mlx_pixel_put(window->mlx, window->win, vars.x, vars.y, color);
		vars.offset += vars.delta;
		if (vars.offset >= vars.threshold)
		{
			vars.x += vars.adjust;
			vars.threshold += vars.thresholdInc;
		}
		vars.y++;
	}
}

void	vertical_line(t_bres vars, t_win *window, int color)
{
	if (vars.y2 < vars.y1)
	{
		vars.tmpy = vars.y1;
		vars.y1 = vars.y2;
		vars.y2 = vars.tmpy;
	}
	vars.y = vars.y1;
	while (vars.y <= vars.y2)
	{
		mlx_pixel_put(window->mlx, window->win, vars.x1, vars.y, color);
		vars.y++;
	}
}

void	bresenham(t_point pt_a, t_point pt_b, int color, t_env env)
{
	t_bres	vars;

	vars.offsetx = env.screen_width / 2;
	vars.offsety = env.screen_height / 2;
	vars.x1 = pt_a.x + vars.offsetx;
	vars.y1 = pt_a.y + vars.offsety;
	vars.x2 = pt_b.x + vars.offsetx;
	vars.y2 = pt_b.y + vars.offsety;
	vars.rise = vars.y2 - vars.y1;
	vars.run = vars.x2 - vars.x1;
	if (!vars.run)
		vertical_line(vars, env.window, color);
	else
	{
		vars.m = vars.rise / vars.run;
		vars.adjust = (vars.m >= 0) ? 1 : -1;
		vars.offset = 0;
		if (-1 <= vars.m && vars.m <= 1)
			run_over_rise(vars, env.window, color);
		else
			rise_over_run(vars, env.window, color);
	}
}
