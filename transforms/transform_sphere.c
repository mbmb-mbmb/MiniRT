/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_sphere_transform.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:08:34 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/02 11:43:12 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	transform_sphere(t_object *obj)
{
	t_transform_components	trs;
	t_mat					temp;

	trs.translation_mat = translation(obj->sphere.location.x,
			obj->sphere.location.y, obj->sphere.location.z);
	trs.scale_mat = scaling(obj->sphere.radius, obj->sphere.radius,
			obj->sphere.radius);
	temp = multiply_matrices(&trs.translation_mat, &trs.scale_mat);
	set_transform(obj, &temp);
}
