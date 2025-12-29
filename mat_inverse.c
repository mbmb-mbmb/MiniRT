/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_inverse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:07:30 by mbonsdor          #+#    #+#             */
/*   Updated: 2025/12/26 16:07:31 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	calc_subdets_top(t_mat *m, float sub_top[6])
{
	sub_top[0] = m->m[0][0] * m->m[1][1] - m->m[1][0] * m->m[0][1];
	sub_top[1] = m->m[0][0] * m->m[1][2] - m->m[1][0] * m->m[0][2];
	sub_top[2] = m->m[0][0] * m->m[1][3] - m->m[1][0] * m->m[0][3];
	sub_top[3] = m->m[0][1] * m->m[1][2] - m->m[1][1] * m->m[0][2];
	sub_top[4] = m->m[0][1] * m->m[1][3] - m->m[1][1] * m->m[0][3];
	sub_top[5] = m->m[0][2] * m->m[1][3] - m->m[1][2] * m->m[0][3];
}

static void	calc_subdets_bot(t_mat *m, float sub_bot[6])
{
	sub_bot[0] = m->m[2][0] * m->m[3][1] - m->m[3][0] * m->m[2][1];
	sub_bot[1] = m->m[2][0] * m->m[3][2] - m->m[3][0] * m->m[2][2];
	sub_bot[2] = m->m[2][0] * m->m[3][3] - m->m[3][0] * m->m[2][3];
	sub_bot[3] = m->m[2][1] * m->m[3][2] - m->m[3][1] * m->m[2][2];
	sub_bot[4] = m->m[2][1] * m->m[3][3] - m->m[3][1] * m->m[2][3];
	sub_bot[5] = m->m[2][2] * m->m[3][3] - m->m[3][2] * m->m[2][3];
}

static void	build_inverse_matrix(t_mat *inv, t_mat *m, float s[6], float c[6], float inv_det)
{
	inv->type = FOUR;
	inv->m[0][0] = (m->m[1][1] * c[5] - m->m[1][2] * c[4] + m->m[1][3] * c[3]) * inv_det;
	inv->m[0][1] = (-m->m[0][1] * c[5] + m->m[0][2] * c[4] - m->m[0][3] * c[3]) * inv_det;
	inv->m[0][2] = (m->m[3][1] * s[5] - m->m[3][2] * s[4] + m->m[3][3] * s[3]) * inv_det;
	inv->m[0][3] = (-m->m[2][1] * s[5] + m->m[2][2] * s[4] - m->m[2][3] * s[3]) * inv_det;
	inv->m[1][0] = (-m->m[1][0] * c[5] + m->m[1][2] * c[2] - m->m[1][3] * c[1]) * inv_det;
	inv->m[1][1] = (m->m[0][0] * c[5] - m->m[0][2] * c[2] + m->m[0][3] * c[1]) * inv_det;
	inv->m[1][2] = (-m->m[3][0] * s[5] + m->m[3][2] * s[2] - m->m[3][3] * s[1]) * inv_det;
	inv->m[1][3] = (m->m[2][0] * s[5] - m->m[2][2] * s[2] + m->m[2][3] * s[1]) * inv_det;
	inv->m[2][0] = (m->m[1][0] * c[4] - m->m[1][1] * c[2] + m->m[1][3] * c[0]) * inv_det;
	inv->m[2][1] = (-m->m[0][0] * c[4] + m->m[0][1] * c[2] - m->m[0][3] * c[0]) * inv_det;
	inv->m[2][2] = (m->m[3][0] * s[4] - m->m[3][1] * s[2] + m->m[3][3] * s[0]) * inv_det;
	inv->m[2][3] = (-m->m[2][0] * s[4] + m->m[2][1] * s[2] - m->m[2][3] * s[0]) * inv_det;
	inv->m[3][0] = (-m->m[1][0] * c[3] + m->m[1][1] * c[1] - m->m[1][2] * c[0]) * inv_det;
	inv->m[3][1] = (m->m[0][0] * c[3] - m->m[0][1] * c[1] + m->m[0][2] * c[0]) * inv_det;
	inv->m[3][2] = (-m->m[3][0] * s[3] + m->m[3][1] * s[1] - m->m[3][2] * s[0]) * inv_det;
	inv->m[3][3] = (m->m[2][0] * s[3] - m->m[2][1] * s[1] + m->m[2][2] * s[0]) * inv_det;
}

t_mat	invert_matrix(t_mat *m)
{
	t_mat	inv;
	float	det;
	float	sub_top[6];
	float	sub_bot[6];

	calc_subdets_top(m, sub_top);
	calc_subdets_bot(m, sub_bot);
	det = sub_top[0] * sub_bot[5] - sub_top[1] * sub_bot[4] + sub_top[2] * sub_bot[3]
	+ sub_top[3] * sub_bot[2] - sub_top[4] * sub_bot[1] + sub_top[5] * sub_bot[0];
	if (is_float_zero(det))
		return (create_identity_matrix(4));
	det = 1.0f / det;
	build_inverse_matrix(&inv, m, sub_top, sub_bot, det);
	set_matrix_dim(&inv, 4);
	return (inv);
}