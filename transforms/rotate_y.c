/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_y.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:08:44 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/05 15:54:55 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_mat	rotate_y(float y)
{
	t_mat	mat;

	mat = create_identity_matrix(4);
	mat.m[0][0] = cos(y);
	mat.m[0][2] = sin(y);
	mat.m[2][0] = -sin(y);
	mat.m[2][2] = cos(y);
	return (mat);
}
