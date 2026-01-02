/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:07:10 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/02 11:07:59 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	reflect(t_tuple *vec, t_tuple *normal)
{
	t_tuple	v_reflected;
	t_tuple	v_temp;
	float	dot;

	dot = dot_product_tuple(vec, normal);
	v_temp = multiply_tuple(normal, 2.0f * dot);
	v_reflected = subtract_tuple(vec, &v_temp);
	return (v_reflected);
}

bool	is_shadowed(t_system *sys, t_tuple *light_pos, t_tuple *over_point)
{
	t_intersection_list	shadow_inters;
	t_intersection		*shadow_hit;
	t_ray				shadow_ray;
	t_tuple				overpoint_to_light;
	float				distance;

	overpoint_to_light = subtract_tuple(light_pos, over_point);
	distance = magnitude_vector(&overpoint_to_light);
	shadow_ray.direction = normalize_vector(&overpoint_to_light);
	shadow_ray.origin = *over_point;
	shadow_inters = intersect_world(sys, &shadow_ray);
	shadow_hit = hit(&shadow_inters);
	if (shadow_hit != NULL && shadow_hit->t < distance)
		return (true);
	return (false);
}

t_shader_computs	prepare_shading_computations(t_intersection *hit, t_ray *world_ray)
{
	t_shader_computs		comps;
	t_tuple					offset;

	comps.point = ray_position(world_ray, hit->t);
	comps.eyev = negate_tuple(&world_ray->direction);
	comps.inside = false;
	if (hit->object->type == SPHERE)
		comps.normalv = normal_at(&hit->object->sphere, &comps.point);
	else if (hit->object->type == PLANE)
		comps.normalv = normal_at_plane(&hit->object->plane);
	else if (hit->object->type == CYLINDER)
		comps.normalv = normal_at_cylinder(&hit->object->cylinder, &comps.point);
	if (dot_product_tuple(&comps.normalv, &comps.eyev) < 0)
	{
		comps.inside = true;
		comps.normalv = negate_tuple(&comps.normalv);
	}
	offset = multiply_tuple(&comps.normalv, SHADOW_EPSILON);
	comps.over_point = add_tuple(&comps.point, &offset);
	return (comps);
}
