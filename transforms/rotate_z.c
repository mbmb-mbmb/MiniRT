/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_z.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:08:44 by mbonsdor          #+#    #+#             */
/*   Updated: 2025/12/26 16:08:45 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_mat	rotate_z(float z)
{
	t_mat	mat;

	mat = create_identity_matrix(4);
	mat.m[0][0] = cos(z);
	mat.m[0][1] = -sin(z);
	mat.m[1][0] = sin(z);
	mat.m[1][1] = cos(z);
	return (mat);
}
