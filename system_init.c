/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:08:34 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/02 11:43:12 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_system(t_system *sys)
{
	*sys = (t_system){0};
	sys->state = DRAFT_MODE;
	sys->exit_code = 0;
	sys->camera.aspect_ratio = (float)WIDTH / (float)HEIGHT;
}

void	init_canvas_dimensions(t_camera *camera, uint32_t img_width)
{
	float	half_view;

	half_view = tanf(degrees_to_radians((float)camera->fov) / 2.0f);
	if (camera->aspect_ratio >= 1.0f)
	{
		camera->canvas_dims.half_width = half_view;
		camera->canvas_dims.half_height = half_view / camera->aspect_ratio;
	}
	else
	{
		camera->canvas_dims.half_width = half_view * camera->aspect_ratio;
		camera->canvas_dims.half_height = half_view;
	}
	camera->canvas_dims.pixel_size = (camera->canvas_dims.half_width
			* 2.0f) / (float)img_width;
}

void	prepare_scene(t_system *sys)
{
	int	i;

	camera_transform(&sys->camera);
	init_canvas_dimensions(&sys->camera, WIDTH);
	i = 0;
	while (i < sys->object_count)
	{
		if (sys->obj_list[i].type == SPHERE)
			setup_sphere_transform(&sys->obj_list[i]);
		else if (sys->obj_list[i].type == PLANE)
			transform_plane(&sys->obj_list[i]);
		else if (sys->obj_list[i].type == CYLINDER)
			transform_cylinder(&sys->obj_list[i]);
		i++;
	}
}
