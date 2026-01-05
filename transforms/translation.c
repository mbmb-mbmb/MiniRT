/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_basic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:08:40 by mbonsdor          #+#    #+#             */
/*   Updated: 2025/12/26 16:08:41 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_mat	translation(float x, float y, float z)
{
	t_mat	mat;

	mat = create_identity_matrix(4);
	mat.m[0][3] = x;
	mat.m[1][3] = y;
	mat.m[2][3] = z;
	return (mat);
}
