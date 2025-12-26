/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_components.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:07:04 by mbonsdor          #+#    #+#             */
/*   Updated: 2025/12/26 16:07:05 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	calculate_ambient(t_material *material, t_amb_light *amb_light)
{
	t_tuple	ambient;
	t_tuple	color;
	t_tuple	with_range;

	color = multiply_tuple_w_tuple(&material->color, &amb_light->color);
	ambient = multiply_tuple(&color, material->ambient);
	with_range = multiply_tuple(&ambient, amb_light->range);
	return (with_range);
}

bool	is_light_behind_surface(t_tuple *light_dir, t_tuple *normal)
{
	return (dot_product_tuple(light_dir, normal) < 0);
}

t_tuple	calculate_diffuse(t_material *material, t_spot_light *light, t_shader_computations *comps)
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

t_tuple	calculate_specular(t_material *material, t_spot_light *light, t_shader_computations *comps)
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
	factor = powf(dot_product_tuple(&reflectv, &comps->eyev), material->shininess);
	specular = multiply_tuple(&light->color,
					material->specular * light->range * factor);
	specular.w = 1.0f;
	return (specular);
}

t_tuple	calc_light_direction(t_tuple *light_pos, t_tuple *point)
{
	t_tuple	direction;

	direction = subtract_tuple(light_pos, point);
	return (normalize_vector(&direction));
}
