/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_for_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyniemit <jyniemit@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:22:14 by jyniemit          #+#    #+#             */
/*   Updated: 2026/01/05 14:22:15 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static t_tuple	compute_pixel_on_canvas(t_camera *camera, uint32_t x,
		uint32_t y)
{
	float	world_x;
	float	world_y;

	world_x = camera->canvas_dims.half_width - ((float)x + 0.5f)
		* camera->canvas_dims.pixel_size;
	world_y = camera->canvas_dims.half_height - ((float)y + 0.5f)
		* camera->canvas_dims.pixel_size;
	return (create_point(world_x, world_y, -1.0f));
}

t_ray	ray_for_pixel(t_camera *camera, uint32_t x, uint32_t y)
{
	t_ray	ray;
	t_tuple	pixel_on_canvas;
	t_tuple	pixel_in_world;
	t_tuple	direction;

	pixel_on_canvas = compute_pixel_on_canvas(camera, x, y);
	pixel_in_world = transform_tuple_by_matrix(&camera->inverse,
			&pixel_on_canvas);
	direction = subtract_tuple(&pixel_in_world, &camera->world_origin);
	ray.origin = camera->world_origin;
	ray.direction = normalize_vector(&direction);
	return (ray);
}
