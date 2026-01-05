/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:08:21 by mbonsdor          #+#    #+#             */
/*   Updated: 2025/12/26 16:08:22 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	ray_make(t_tuple origin, t_tuple direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

t_tuple	ray_position(t_ray *ray, float t)
{
	t_tuple	v_pos;
	t_tuple	v_dirmult;

	v_dirmult = multiply_tuple(&ray->direction, t);
	v_pos = add_tuple(&ray->origin, &v_dirmult);
	return (v_pos);
}

t_ray	ray_transform(t_ray *ray, t_mat *mat)
{
	t_ray	ray_out;

	ray_out.origin = transform_tuple_by_matrix(mat, &ray->origin);
	ray_out.direction = transform_tuple_by_matrix(mat, &ray->direction);
	ray_out.origin.w = POINT;
	ray_out.direction.w = VECTOR;
	return (ray_out);
}

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
