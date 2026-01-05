/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyniemit <jyniemit@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 16:08:09 by jyniemit          #+#    #+#             */
/*   Updated: 2026/01/04 16:08:11 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_tuple	calculate_light_contribution(t_system *sys, t_material *mat,
		t_shader_computs *comps, int i)
{
	t_tuple	color;
	t_tuple	contrib;

	color = create_color(0, 0, 0, 1);
	comps->light_dir = calculate_light_direction(&sys->light_list[i].location,
			&comps->point);
	contrib = calculate_diffuse(mat, &sys->light_list[i], comps);
	color = add_tuple(&color, &contrib);
	contrib = calculate_specular(mat, &sys->light_list[i], comps);
	color = add_tuple(&color, &contrib);
	return (color);
}

t_tuple	shade_hit(t_system *sys, t_material *mat, t_shader_computs *comps)
{
	t_tuple	color;
	t_tuple	contrib;
	int		i;
	int		light_limit;

	color = calculate_ambient(mat, &sys->amb_light);
	if (sys->render_flags & RENDER_SKIP_MULTILIGHT)
		light_limit = 1;
	else
		light_limit = sys->light_count;
	i = 0;
	while (i < light_limit)
	{
		if ((sys->render_flags & RENDER_SKIP_SHADOWS) || !is_shadowed(sys,
				&sys->light_list[i].location, &comps->over_point))
		{
			contrib = calculate_light_contribution(sys, mat, comps, i);
			color = add_tuple(&color, &contrib);
		}
		i++;
	}
	return (color);
}

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
