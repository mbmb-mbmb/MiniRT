/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:07:25 by mbonsdor          #+#    #+#             */
/*   Updated: 2025/12/26 16:07:26 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


t_mat	create_identity_matrix(int dim)
{
	t_mat	mat;
	int		i;
	int		j;

	i = 0;
	while (i < dim)
	{
		j = 0;
		while (j < dim)
		{
			if (i == j)
				mat.m[i][j] = 1;
			else
				mat.m[i][j] = 0;
			j++;
		}
		i++;
	}
	set_matrix_dim(&mat, dim);
	return (mat);
}

// t_mat	create_matrix_2(float m[2][2])
// {
// 	t_mat	matrix;

// 	matrix = (t_mat){};
// 	matrix.type = TWO;
// 	matrix.m[0][0] = m[0][0];
// 	matrix.m[0][1] = m[0][1];
// 	matrix.m[1][0] = m[1][0];
// 	matrix.m[1][1] = m[1][1];
// 	return (matrix);
// }

// t_mat	create_matrix_3(float m[3][3])
// {
// 	t_mat	matrix;

// 	matrix = (t_mat){};
// 	matrix.type = THREE;
// 	matrix.m[0][0] = m[0][0];
// 	matrix.m[0][1] = m[0][1];
// 	matrix.m[0][2] = m[0][2];
// 	matrix.m[1][0] = m[1][0];
// 	matrix.m[1][1] = m[1][1];
// 	matrix.m[1][2] = m[1][2];
// 	matrix.m[2][0] = m[2][0];
// 	matrix.m[2][1] = m[2][1];
// 	matrix.m[2][2] = m[2][2];
// 	return (matrix);
// }
