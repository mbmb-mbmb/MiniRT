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

t_tuple	color_at(t_system *sys, t_ray *ray)
{
	t_intersection_list	intersections;
	t_shader_computations	comps;
	t_intersection		*closest_hit;
	t_tuple				color;

	intersections = intersect_world(sys, ray);
	closest_hit = hit(&intersections);
	if (closest_hit == NULL)
		return (create_color(0, 0, 0, 1));
	comps = prepare_shading_computitions(closest_hit, ray);
	if (closest_hit->object->type == SPHERE)
		color = lighting(&closest_hit->object->sphere.material,
					&sys->amb_light,
					&sys->light_list[0],
					&comps);
	else if (closest_hit->object->type == PLANE)
		color = lighting(&closest_hit->object->plane.material,
					&sys->amb_light,
					&sys->light_list[0],
					&comps);
	else if (closest_hit->object->type == CYLINDER)
		color = lighting(&closest_hit->object->cylinder.material,
					&sys->amb_light,
					&sys->light_list[0],
					&comps);
	else
		color = create_color(0, 0, 0, 1);
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
