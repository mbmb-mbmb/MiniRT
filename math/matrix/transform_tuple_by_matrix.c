/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_tuple_by_matrix.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:07:35 by mbonsdor          #+#    #+#             */
/*   Updated: 2025/12/26 16:07:36 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

t_tuple	transform_tuple_by_matrix(t_mat *mat, t_tuple *in)
{
	t_tuple	out;

	out.x = mat->m[0][0] * in->x + mat->m[0][1] * in->y + mat->m[0][2] * in->z
		+ mat->m[0][3] * in->w;
	out.y = mat->m[1][0] * in->x + mat->m[1][1] * in->y + mat->m[1][2] * in->z
		+ mat->m[1][3] * in->w;
	out.z = mat->m[2][0] * in->x + mat->m[2][1] * in->y + mat->m[2][2] * in->z
		+ mat->m[2][3] * in->w;
	out.w = mat->m[3][0] * in->x + mat->m[3][1] * in->y + mat->m[3][2] * in->z
		+ mat->m[3][3] * in->w;
	return (out);
}
