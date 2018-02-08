/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 21:30:17 by kcheung           #+#    #+#             */
/*   Updated: 2018/02/07 17:10:16 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_points(t_env env, t_point **plot)
{
	int	row;
	int	col;

	row = 0;
	while (plot[row])
	{
		col = 0;
		while (col < env.col_count)
		{
			printf("(%d,%d,%d) ", plot[row][col].x,
					plot[row][col].y, plot[row][col].z);
			col++;
		}
		printf("\n");
		row++;
	}
}

int		main(int argc, char **argv)
{
	static t_win	*window;
	t_env			env;

	if (argc != 2)
	{
		printf("Usage:./fdf [filepath]\n");
		return (0);
	}
	init_env(&env, argv);
	window = (t_win *)malloc(sizeof(t_win));
	window->count = 10;
	window->mlx = mlx_init();
	window->win = mlx_new_window(window->mlx, env.screen_width,
			env.screen_height, "Deadly Signal");
	env.window = window;
	fdf_display(env, env.cart_points);
	mlx_key_hook(window->win, my_key_func, &env);
	mlx_mouse_hook(window->win, mouse_hook, &env);
	mlx_loop(window->mlx);
}
