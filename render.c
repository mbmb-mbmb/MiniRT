/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:08:24 by mbonsdor          #+#    #+#             */
/*   Updated: 2025/12/26 16:08:25 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_tuple	shade_hit(t_system *sys, t_material *mat,
				t_shader_computations *comps)
{
	t_tuple	color;
	t_tuple	contrib;
	int		i;

	color = calculate_ambient(mat, &sys->amb_light);
	i = 0;
	while (i < sys->light_count)
	{
		if (!is_shadowed(sys, &sys->light_list[i].location, &comps->over_point))
		{
			comps->light_dir = calculate_light_direction(
					&sys->light_list[i].location, &comps->point);
			contrib = calculate_diffuse(mat, &sys->light_list[i], comps);
			color = add_tuple(&color, &contrib);
			contrib = calculate_specular(mat, &sys->light_list[i], comps);
			color = add_tuple(&color, &contrib);
		}
		i++;
	}
	return (color);
}

t_tuple	color_at(t_system *sys, t_ray *ray)
{
	t_intersection_list		intersections;
	t_shader_computations	comps;
	t_intersection			*closest_hit;
	t_material				*mat;
	t_tuple					color;

	intersections = intersect_world(sys, ray);
	closest_hit = hit(&intersections);
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

void	render(t_system *sys, mlx_image_t *img)
{
	int		x;
	int		y;
	t_ray	ray;
	t_tuple	color;

	y = 0;
	while (y < (int)img->height)
	{
		x = 0;
		while (x < (int)img->width)
		{
			ray = ray_for_pixel(&sys->camera, (uint32_t)x, (uint32_t)y, img);
			color = color_at(sys, &ray);
			mlx_put_pixel(img, x, y, tuple_to_rgba(&color));
			x++;
		}
		y++;
	}
}
