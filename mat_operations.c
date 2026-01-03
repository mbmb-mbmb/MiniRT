/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:07:35 by mbonsdor          #+#    #+#             */
/*   Updated: 2025/12/26 16:07:36 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_mat	multiply_matrices(t_mat *a, t_mat *b)
{
	t_mat	out;
	int		i;
	int		j;

	out = (t_mat){0};
	out.type = a->type;
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			out.m[i][j] = a->m[i][0] * b->m[0][j]
				+ a->m[i][1] * b->m[1][j]
				+ a->m[i][2] * b->m[2][j]
				+ a->m[i][3] * b->m[3][j];
			j++;
		}
		i++;
	}
	return (out);
}

t_tuple	multiply_matrix_and_tuple(t_mat *mat, t_tuple *in)
{
	t_tuple	out;

	out.x = mat->m[0][0] * in->x + mat->m[0][1] * in->y
		+ mat->m[0][2] * in->z + mat->m[0][3] * in->w;
	out.y = mat->m[1][0] * in->x + mat->m[1][1] * in->y
		+ mat->m[1][2] * in->z + mat->m[1][3] * in->w;
	out.z = mat->m[2][0] * in->x + mat->m[2][1] * in->y
		+ mat->m[2][2] * in->z + mat->m[2][3] * in->w;
	out.w = mat->m[3][0] * in->x + mat->m[3][1] * in->y
		+ mat->m[3][2] * in->z + mat->m[3][3] * in->w;
	return (out);
}

t_mat	transpose_matrix(t_mat *mat, int dim)
{
	int		i;
	int		j;
	t_mat	mat_trans;

	mat_trans.type = mat->type;
	i = 0;
	while (i < dim)
	{
		j = 0;
		while (j < dim)
		{
			mat_trans.m[j][i] = mat->m[i][j];
			j++;
		}
		i++;
	}
	return (mat_trans);
}

void	set_matrix_dim(t_mat *mat, int dim)
{
	if (dim == 3)
		mat->type = THREE;
	else if (dim == 2)
		mat->type = TWO;
	else if (dim == 4)
		mat->type = FOUR;
	else
		mat->type = -1;
}

// bool	matrices_are_equal(t_mat *a, t_mat *b)
// {
// 	int		row;
// 	int		col;
// 	int		dim;

// 	dim = get_matrix_dim(a, b);
// 	if (dim == -1)
// 		return (false);
// 	row = 0;
// 	while (row < dim)
// 	{
// 		col = 0;
// 		while (col < dim)
// 		{
// 			if (!is_float_equal(a->m[row][col], b->m[row][col]))
// 				return (false);
// 			col++;
// 		}
// 		row++;
// 	}
// 	return (true);
// }