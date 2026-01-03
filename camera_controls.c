/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_controls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyniemit <jyniemit@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 14:05:23 by jyniemit          #+#    #+#             */
/*   Updated: 2026/01/03 14:05:28 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	camera_move(t_camera *camera, float dx, float dy, float dz)
{
	t_tuple	forward;
	t_tuple	right;
	t_tuple	up;
	t_tuple	movement;

	forward = normalize_vector(&camera->rotation);
	up = create_vector(0, 1, 0);
	right = cross_product_tuple(&forward, &up);
	right = normalize_vector(&right);
	movement = create_vector(0, 0, 0);
	if (dx != 0.0f)
	{
		right = multiply_tuple(&right, dx);
		movement = add_tuple(&movement, &right);
	}
	if (dy != 0.0f)
	{
		up = multiply_tuple(&up, dy);
		movement = add_tuple(&movement, &up);
	}
	if (dz != 0.0f)
	{
		forward = multiply_tuple(&forward, dz);
		movement = add_tuple(&movement, &forward);
	}
	camera->location = add_tuple(&camera->location, &movement);
}

void	camera_rotate_yaw(t_camera *camera, float angle)
{
	t_mat	rotation;
	t_tuple	new_rotation;

	rotation = rotate_y(angle);
	new_rotation = multiply_matrix_and_tuple(&rotation, &camera->rotation);
	camera->rotation = normalize_vector(&new_rotation);
}

void	camera_reset(t_camera *camera)
{
	camera->location = camera->original_location;
	camera->rotation = camera->original_rotation;
}
