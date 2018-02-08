/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 16:47:10 by kcheung           #+#    #+#             */
/*   Updated: 2018/01/29 18:45:28 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	calc_pixel_size(t_env env)
{
	float		spacing;

	if (env.col_count > env.row_count)
		spacing = (env.screen_width / env.col_count) * .60;
	else
		spacing = (env.screen_height / env.row_count) * .60;
	return (spacing);
}

void	validate_assign(t_env *env, char *str, int row, int col)
{
	int		num;

	num = 0;
	if ((num = ft_atoi(str)) == 0 && ft_strcmp(str, "0"))
	{
		ft_putstr_fd("Error:Invalid map\n", 2);
		exit(-1);
	}
	if (num > env->z_max)
		env->z_max = num;
	else if (num < env->z_min)
		env->z_min = num;
	env->map[row][col] = num;
}

/* Read map from file */
void	ft_getmap(t_env *env, int fd)
{
	char	*line;
	char	**array;
	int		row;
	int		col;

	row = 0;
	while (get_next_line(fd, &line) > 0)
	{
		(row >= env->row_count) ? resize_row(env) : resize_row(NULL);
		col = 0;
		array = ft_toksplit(line, " ");
		if (!(env->map[row] = (int *)malloc(sizeof(int) * env->col_count)))
			exit(-1);
		while (*array)
		{
			(col >= env->col_count) ? resize_col(env, row) :
				resize_col(NULL, row);
			validate_assign(env, *array, row, col);
			array++;
			col++;
		}
		row++;
	}
	env->map[row] = NULL;
}

t_point	**get_plot(t_env env, int **array)
{
	int			i;
	int			j;
	int			a[2];
	t_point		**m;

	m = malloc_matrix(env);
	i = -1;
	a[1] = 0;
	while (array[++i])
	{
		j = -1;
		a[0] = 0;
		while (++j < env.col_count)
		{
			m[i][j].x = a[0] - (((env.col_count - 1) * env.spacing) / 2);
			m[i][j].y = a[1] - (((env.row_count - 1) * env.spacing) / 2);
			m[i][j].z = array[i][j];
			a[0] = a[0] + env.spacing;
		}
		a[1] = a[1] + env.spacing;
	}
	return (m);
}

void	init_env(t_env *env, char **argv)
{
	int fd;

	if ((fd = open(argv[1], O_RDONLY)) < 0)
	{
		perror("Invalid file\n");
		exit(-1);
	}
	env->row_count = 0;
	env->col_count = 0;
	env->map = NULL;
	ft_getmap(env, fd);
	env->screen_width = 2500;
	env->screen_height = 1300;
	env->spacing = calc_pixel_size(*env);
	env->cart_points = get_plot(*env, env->map);
	env->degrees.x = 0;
	env->degrees.y = 0;
	env->degrees.z = 0;
	env->degrees.s = 1;
}
