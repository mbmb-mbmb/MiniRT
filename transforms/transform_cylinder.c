/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyniemit <jyniemit@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:54:28 by jyniemit          #+#    #+#             */
/*   Updated: 2026/01/05 15:54:28 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	transform_cylinder(t_object *obj)
{
	t_transform_components	tr;
	t_mat					temp;
	t_mat					final;
	float					radius;

	radius = obj->cylinder.diameter / 2.0f;
	tr.translation_mat = translation(obj->cylinder.location.x,
			obj->cylinder.location.y, obj->cylinder.location.z);
	tr.rotation_mat = create_rotation_matrix_from_axis(&obj->cylinder.rotation);
	tr.scale_mat = scaling(radius, obj->cylinder.length / 2.0f, radius);
	temp = multiply_matrices(&tr.rotation_mat, &tr.scale_mat);
	final = multiply_matrices(&tr.translation_mat, &temp);
	set_transform(obj, &final);
}
