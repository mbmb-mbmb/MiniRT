/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_inverse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:07:30 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/01 12:11:26 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	calc_subdets_top(t_mat *m, float subdets_01[6])
{
	subdets_01[0] = m->m[0][0] * m->m[1][1] - m->m[1][0] * m->m[0][1];
	subdets_01[1] = m->m[0][0] * m->m[1][2] - m->m[1][0] * m->m[0][2];
	subdets_01[2] = m->m[0][0] * m->m[1][3] - m->m[1][0] * m->m[0][3];
	subdets_01[3] = m->m[0][1] * m->m[1][2] - m->m[1][1] * m->m[0][2];
	subdets_01[4] = m->m[0][1] * m->m[1][3] - m->m[1][1] * m->m[0][3];
	subdets_01[5] = m->m[0][2] * m->m[1][3] - m->m[1][2] * m->m[0][3];
}

static void	calc_subdets_bot(t_mat *m, float subdets_23[6])
{
	subdets_23[0] = m->m[2][0] * m->m[3][1] - m->m[3][0] * m->m[2][1];
	subdets_23[1] = m->m[2][0] * m->m[3][2] - m->m[3][0] * m->m[2][2];
	subdets_23[2] = m->m[2][0] * m->m[3][3] - m->m[3][0] * m->m[2][3];
	subdets_23[3] = m->m[2][1] * m->m[3][2] - m->m[3][1] * m->m[2][2];
	subdets_23[4] = m->m[2][1] * m->m[3][3] - m->m[3][1] * m->m[2][3];
	subdets_23[5] = m->m[2][2] * m->m[3][3] - m->m[3][2] * m->m[2][3];
}

static void	build_inverse_matrix(t_mat *inv, t_mat *m, float inv_det)
{
	float	t[6];
	float	b[6];

	calc_subdets_top(m, t);
	calc_subdets_bot(m, b);
	inv->type = FOUR;
	inv->m[0][0] = (m->m[1][1] * b[5] - m->m[1][2] * b[4] + m->m[1][3] * b[3]) * inv_det;
	inv->m[0][1] = (-m->m[0][1] * b[5] + m->m[0][2] * b[4] - m->m[0][3] * b[3]) * inv_det;
	inv->m[0][2] = (m->m[3][1] * t[5] - m->m[3][2] * t[4] + m->m[3][3] * t[3]) * inv_det;
	inv->m[0][3] = (-m->m[2][1] * t[5] + m->m[2][2] * t[4] - m->m[2][3] * t[3]) * inv_det;
	inv->m[1][0] = (-m->m[1][0] * b[5] + m->m[1][2] * b[2] - m->m[1][3] * b[1]) * inv_det;
	inv->m[1][1] = (m->m[0][0] * b[5] - m->m[0][2] * b[2] + m->m[0][3] * b[1]) * inv_det;
	inv->m[1][2] = (-m->m[3][0] * t[5] + m->m[3][2] * t[2] - m->m[3][3] * t[1]) * inv_det;
	inv->m[1][3] = (m->m[2][0] * t[5] - m->m[2][2] * t[2] + m->m[2][3] * t[1]) * inv_det;
	inv->m[2][0] = (m->m[1][0] * b[4] - m->m[1][1] * b[2] + m->m[1][3] * b[0]) * inv_det;
	inv->m[2][1] = (-m->m[0][0] * b[4] + m->m[0][1] * b[2] - m->m[0][3] * b[0]) * inv_det;
	inv->m[2][2] = (m->m[3][0] * t[4] - m->m[3][1] * t[2] + m->m[3][3] * t[0]) * inv_det;
	inv->m[2][3] = (-m->m[2][0] * t[4] + m->m[2][1] * t[2] - m->m[2][3] * t[0]) * inv_det;
	inv->m[3][0] = (-m->m[1][0] * b[3] + m->m[1][1] * b[1] - m->m[1][2] * b[0]) * inv_det;
	inv->m[3][1] = (m->m[0][0] * b[3] - m->m[0][1] * b[1] + m->m[0][2] * b[0]) * inv_det;
	inv->m[3][2] = (-m->m[3][0] * t[3] + m->m[3][1] * t[1] - m->m[3][2] * t[0]) * inv_det;
	inv->m[3][3] = (m->m[2][0] * t[3] - m->m[2][1] * t[1] + m->m[2][2] * t[0]) * inv_det;
}

t_mat	invert_matrix(t_mat *m)
{
	t_mat	inv;
	float	det;
	float	subdets_01[6];
	float	subdets_23[6];

	calc_subdets_top(m, subdets_01);
	calc_subdets_bot(m, subdets_23);
	det = subdets_01[0] * subdets_23[5] - subdets_01[1] * subdets_23[4] + subdets_01[2] * subdets_23[3]
		+ subdets_01[3] * subdets_23[2] - subdets_01[4] * subdets_23[1] + subdets_01[5] * subdets_23[0];
	if (is_float_zero(det))
		return (create_identity_matrix(4));
	det = 1.0f / det;
	build_inverse_matrix(&inv, m, det);
	set_matrix_dim(&inv, 4);
	return (inv);
}
