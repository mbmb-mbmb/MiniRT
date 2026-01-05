/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_shadowed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:07:10 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/02 11:16:33 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

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
	shadow_hit = find_closest_intersection(&shadow_inters);
	if (shadow_hit != NULL && shadow_hit->t < distance)
		return (true);
	return (false);
}
