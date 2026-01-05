/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade_hit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyniemit <jyniemit@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 16:08:09 by jyniemit          #+#    #+#             */
/*   Updated: 2026/01/05 15:54:56 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static t_tuple	calculate_light_contribution(t_system *sys, t_material *mat,
		t_shader_computs *comps, int i)
{
	t_tuple	color;
	t_tuple	contrib;

	color = create_color(0, 0, 0, 1);
	comps->light_dir = calculate_point_to_light_direction(
			&sys->light_list[i].location, &comps->point);
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
