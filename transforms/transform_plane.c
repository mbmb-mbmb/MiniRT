/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:08:34 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/02 11:43:12 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	transform_plane(t_object *obj)
{
	t_mat					temp;
	t_transform_components	trs;

	trs.translation_mat = translation(obj->plane.location.x,
			obj->plane.location.y, obj->plane.location.z);
	trs.rotation_mat = create_rotation_matrix_from_axis(&obj->plane.rotation);
	temp = multiply_matrices(&trs.translation_mat, &trs.rotation_mat);
	set_transform(obj, &temp);
}
