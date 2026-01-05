/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_canvas_dimensions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:08:34 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/02 11:43:12 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

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
	camera->canvas_dims.pixel_size = (camera->canvas_dims.half_width * 2.0f)
		/ (float)img_width;
}
