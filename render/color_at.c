/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_at.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyniemit <jyniemit@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 16:08:09 by jyniemit          #+#    #+#             */
/*   Updated: 2026/01/05 15:54:57 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_tuple	color_at(t_system *sys, t_ray *ray)
{
	t_intersection_list	intersections;
	t_shader_computs	comps;
	t_intersection		*closest_hit;
	t_material			*mat;
	t_tuple				color;

	intersections = intersect_world(sys, ray);
	closest_hit = find_closest_intersection(&intersections);
	if (closest_hit == NULL)
		return (create_color(0, 0, 0, 1));
	mat = &closest_hit->object->material;
	if (mat == NULL)
		return (create_color(0, 0, 0, 1));
	comps = prepare_shading_computations(closest_hit, ray);
	color = shade_hit(sys, mat, &comps);
	color = clamp_tuple(&color, 0.0f, 1.0f);
	color.w = 1.0f;
	return (color);
}
