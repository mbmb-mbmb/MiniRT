/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invert_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:07:30 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/05 14:30:06 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

static void	calc_subdets(t_mat *m, float subdets[12])
{
	subdets[0] = m->m[0][0] * m->m[1][1] - m->m[1][0] * m->m[0][1];
	subdets[1] = m->m[0][0] * m->m[1][2] - m->m[1][0] * m->m[0][2];
	subdets[2] = m->m[0][0] * m->m[1][3] - m->m[1][0] * m->m[0][3];
	subdets[3] = m->m[0][1] * m->m[1][2] - m->m[1][1] * m->m[0][2];
	subdets[4] = m->m[0][1] * m->m[1][3] - m->m[1][1] * m->m[0][3];
	subdets[5] = m->m[0][2] * m->m[1][3] - m->m[1][2] * m->m[0][3];
	subdets[6] = m->m[2][0] * m->m[3][1] - m->m[3][0] * m->m[2][1];
	subdets[7] = m->m[2][0] * m->m[3][2] - m->m[3][0] * m->m[2][2];
	subdets[8] = m->m[2][0] * m->m[3][3] - m->m[3][0] * m->m[2][3];
	subdets[9] = m->m[2][1] * m->m[3][2] - m->m[3][1] * m->m[2][2];
	subdets[10] = m->m[2][1] * m->m[3][3] - m->m[3][1] * m->m[2][3];
	subdets[11] = m->m[2][2] * m->m[3][3] - m->m[3][2] * m->m[2][3];
}

static void	build_inverse_matrix(t_mat *inv, t_mat *mat, float id, float s[12])
{
	float	(*m)[4];

	m = mat->m;
	inv->type = FOUR;
	inv->m[0][0] = (m[1][1] * s[11] - m[1][2] * s[10] + m[1][3] * s[9]) * id;
	inv->m[0][1] = (-m[0][1] * s[11] + m[0][2] * s[10] - m[0][3] * s[9]) * id;
	inv->m[0][2] = (m[3][1] * s[5] - m[3][2] * s[4] + m[3][3] * s[3]) * id;
	inv->m[0][3] = (-m[2][1] * s[5] + m[2][2] * s[4] - m[2][3] * s[3]) * id;
	inv->m[1][0] = (-m[1][0] * s[11] + m[1][2] * s[8] - m[1][3] * s[7]) * id;
	inv->m[1][1] = (m[0][0] * s[11] - m[0][2] * s[8] + m[0][3] * s[7]) * id;
	inv->m[1][2] = (-m[3][0] * s[5] + m[3][2] * s[2] - m[3][3] * s[1]) * id;
	inv->m[1][3] = (m[2][0] * s[5] - m[2][2] * s[2] + m[2][3] * s[1]) * id;
	inv->m[2][0] = (m[1][0] * s[10] - m[1][1] * s[8] + m[1][3] * s[6]) * id;
	inv->m[2][1] = (-m[0][0] * s[10] + m[0][1] * s[8] - m[0][3] * s[6]) * id;
	inv->m[2][2] = (m[3][0] * s[4] - m[3][1] * s[2] + m[3][3] * s[0]) * id;
	inv->m[2][3] = (-m[2][0] * s[4] + m[2][1] * s[2] - m[2][3] * s[0]) * id;
	inv->m[3][0] = (-m[1][0] * s[9] + m[1][1] * s[7] - m[1][2] * s[6]) * id;
	inv->m[3][1] = (m[0][0] * s[9] - m[0][1] * s[7] + m[0][2] * s[6]) * id;
	inv->m[3][2] = (-m[3][0] * s[3] + m[3][1] * s[1] - m[3][2] * s[0]) * id;
	inv->m[3][3] = (m[2][0] * s[3] - m[2][1] * s[1] + m[2][2] * s[0]) * id;
}

t_mat	invert_matrix(t_mat *m)
{
	t_mat	inv;
	float	det;
	float	subdets[12];

	calc_subdets(m, subdets);
	det = subdets[0] * subdets[11] - subdets[1] * subdets[10]
		+ subdets[2] * subdets[9] + subdets[3] * subdets[8]
		- subdets[4] * subdets[7] + subdets[5] * subdets[6];
	if (is_float_zero(det))
		return (create_identity_matrix(4));
	det = 1.0f / det;
	build_inverse_matrix(&inv, m, det, subdets);
	set_matrix_dim(&inv, 4);
	return (inv);
}
