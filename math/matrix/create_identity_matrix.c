/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_identity_matrix.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:07:35 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/05 14:29:30 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

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
