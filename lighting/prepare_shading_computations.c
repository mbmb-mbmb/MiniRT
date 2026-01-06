/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_shading_computations.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:07:10 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/05 14:29:05 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static void	flip_normal_if_inside(t_tuple *normalv, t_tuple *eyev)
{
	if (dot_product_tuple(normalv, eyev) < 0)
	{
		*normalv = negate_tuple(normalv);
	}
}

t_shader_computs	prepare_shading_computations(t_intersection *hit,
		t_ray *world_ray)
{
	t_shader_computs	comps;
	t_tuple				offset;

	comps.point = ray_position(world_ray, hit->t);
	comps.eyev = negate_tuple(&world_ray->direction);
	if (hit->object->type == SPHERE)
		comps.normalv = normal_at_sphere(&hit->object->sphere, &comps.point);
	else if (hit->object->type == PLANE)
		comps.normalv = normal_at_plane(&hit->object->plane);
	else if (hit->object->type == CYLINDER)
		comps.normalv = normal_at_cylinder(&hit->object->cylinder,
				&comps.point);
	flip_normal_if_inside(&comps.normalv, &comps.eyev);
	offset = multiply_tuple(&comps.normalv, SHADOW_EPSILON);
	comps.over_point = add_tuple(&comps.point, &offset);
	return (comps);
}
