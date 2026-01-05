/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_specular.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:07:04 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/05 14:28:44 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static bool	is_light_behind_surface(t_tuple *light_dir, t_tuple *normal)
{
	return (dot_product_tuple(light_dir, normal) < 0);
}

t_tuple	calculate_specular(t_material *material, t_spot_light *light,
		t_shader_computs *comps)
{
	t_tuple	specular;
	t_tuple	neg_lightv;
	t_tuple	reflectv;
	float	factor;

	if (is_light_behind_surface(&comps->light_dir, &comps->normalv))
		return (create_color(0, 0, 0, 1));
	neg_lightv = negate_tuple(&comps->light_dir);
	reflectv = reflect(&neg_lightv, &comps->normalv);
	if (dot_product_tuple(&reflectv, &comps->eyev) < 0)
		return (create_color(0, 0, 0, 1));
	factor = powf(dot_product_tuple(&reflectv, &comps->eyev),
			material->shininess);
	specular = multiply_tuple(&light->color, material->specular * light->range
			* factor);
	specular.w = 1.0f;
	return (specular);
}
