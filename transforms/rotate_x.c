/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_x.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:08:44 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/05 15:54:49 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_mat	rotate_x(float x)
{
	t_mat	mat;

	mat = create_identity_matrix(4);
	mat.m[1][1] = cos(x);
	mat.m[2][1] = -sin(x);
	mat.m[1][2] = sin(x);
	mat.m[2][2] = cos(x);
	return (mat);
}
