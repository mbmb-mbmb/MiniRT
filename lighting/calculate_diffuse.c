/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_diffuse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:07:04 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/05 14:28:28 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static bool	is_light_behind_surface(t_tuple *light_dir, t_tuple *normal)
{
	return (dot_product_tuple(light_dir, normal) < 0);
}

t_tuple	calculate_diffuse(t_material *material, t_spot_light *light,
		t_shader_computs *comps)
{
	t_tuple	diffuse;
	t_tuple	color;
	float	scalar;

	if (is_light_behind_surface(&comps->light_dir, &comps->normalv))
		return (create_color(0, 0, 0, 1));
	color = multiply_tuple_w_tuple(&material->color, &light->color);
	scalar = material->diffuse * light->range
		* dot_product_tuple(&comps->light_dir, &comps->normalv);
	diffuse = multiply_tuple(&color, scalar);
	diffuse.w = 1.0f;
	return (diffuse);
}
