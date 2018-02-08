/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 16:46:41 by kcheung           #+#    #+#             */
/*   Updated: 2017/05/19 18:30:09 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		mouse_hook(int button, int x, int y, t_env *env)
{
	t_point		**new_matrix;

	new_matrix = NULL;
	if (button == 5)
	{
		env->degrees.s += 2;
	}
	else if (button == 4)
	{
		env->degrees.s -= 2;
	}
	new_matrix = update(*env);
	mlx_clear_window(env->window->mlx, env->window->win);
	fdf_display(*env, new_matrix);
	free_matrix(new_matrix);
	(void)x;
	(void)y;
	return (0);
}

void	redraw(t_env *env)
{
	t_point		**new_matrix;

	new_matrix = NULL;
	new_matrix = update(*env);
	mlx_clear_window(env->window->mlx, env->window->win);
	fdf_display(*env, new_matrix);
	free_matrix(new_matrix);
}

int		my_key_func(int keycode, t_env *env)
{
	float			adjust;

	adjust = 10;
	if (keycode == 18)
		env->degrees.z += adjust;
	else if (keycode == 19)
		env->degrees.z -= adjust;
	else if (keycode == 125)
		env->degrees.x -= adjust;
	else if (keycode == 126)
		env->degrees.x += adjust;
	else if (keycode == 123)
		env->degrees.y -= adjust;
	else if (keycode == 124)
		env->degrees.y += adjust;
	else if (keycode == 53)
		exit(1);
	redraw(env);
	return (0);
}
