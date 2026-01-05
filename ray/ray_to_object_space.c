/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_to_object_space.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:08:21 by mbonsdor          #+#    #+#             */
/*   Updated: 2025/12/26 16:08:22 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_ray	ray_to_object_space(t_ray *ray, t_object *obj)
{
	t_ray	obj_ray;

	if (!(obj->flags & OBJ_HAS_TRANSFORM))
	{
		obj_ray = *ray;
		return (obj_ray);
	}
	if (obj->type == SPHERE)
		obj_ray = ray_transform(ray, &obj->sphere.inv_transform_to_obj);
	else if (obj->type == PLANE)
		obj_ray = ray_transform(ray, &obj->plane.inv_transform_to_obj);
	else if (obj->type == CYLINDER)
		obj_ray = ray_transform(ray, &obj->cylinder.inv_transform_to_obj);
	else
		obj_ray = *ray;
	return (obj_ray);
}
