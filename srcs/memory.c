/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheung <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 16:45:47 by kcheung           #+#    #+#             */
/*   Updated: 2017/05/19 18:44:19 by kcheung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	**malloc_matrix(t_env env)
{
	int		i;
	t_point	**plot;

	i = 0;
	if (!(plot = (t_point **)malloc(sizeof(t_point *) * env.row_count + 1)))
	{
		printf("Error:Memory Allocation\n");
		exit(-1);
	}
	while (i < env.row_count)
	{
		if (!(plot[i] = (t_point *)malloc(sizeof(t_point) * env.col_count)))
		{
			printf("Error:Memory Allocation\n");
			exit(-1);
		}
		i++;
	}
	plot[i] = NULL;
	return (plot);
}

void	free_matrix(t_point **matrix)
{
	int		row;
	int		col;

	row = 0;
	while (matrix[row])
	{
		col = 0;
		free(matrix[row]);
		matrix[row] = NULL;
		row++;
	}
}

void	resize_row(t_env *env)
{
	if (env)
	{
		env->row_count += ROW_SIZE;
		if (!env->map)
		{
			env->map = (int **)malloc(sizeof(int *) * 1);
			env->map[0] = NULL;
			if (!env->map)
				exit(-1);
		}
		else if (!(env->map = ft_realloc(env->map,
						env->row_count * sizeof(int*))))
			exit(-1);
	}
}

void	resize_col(t_env *env, int row)
{
	if (env)
	{
		env->col_count += COL_SIZE;
		if (!(env->map[row] = ft_realloc(env->map[row],
						env->col_count * sizeof(int*))))
			exit(-1);
	}
}
