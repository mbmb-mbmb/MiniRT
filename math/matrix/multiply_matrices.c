/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiply_matrices.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:07:35 by mbonsdor          #+#    #+#             */
/*   Updated: 2025/12/26 16:07:36 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

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
			out.m[i][j] = a->m[i][0] * b->m[0][j] + a->m[i][1] * b->m[1][j]
				+ a->m[i][2] * b->m[2][j] + a->m[i][3] * b->m[3][j];
			j++;
		}
		i++;
	}
	return (out);
}
