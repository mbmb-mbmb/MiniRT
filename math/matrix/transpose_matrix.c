/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transpose_matrix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:07:35 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/05 15:03:44 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

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
