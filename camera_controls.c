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

void	add_directional_movement(t_tuple *movement, t_tuple *direction, float x)
{
	t_tuple	multiplied;

	if (x != 0.0f)
	{
		multiplied = multiply_tuple(direction, x);
		*movement = add_tuple(movement, &multiplied);
	}
}

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
	add_directional_movement(&movement, &right, dx);
	add_directional_movement(&movement, &up, dy);
	add_directional_movement(&movement, &forward, dz);
	camera->location = add_tuple(&camera->location, &movement);
}

void	camera_rotate_yaw(t_camera *camera, float angle)
{
	t_mat	rotation;
	t_tuple	new_rotation;

	rotation = rotate_y(angle);
	new_rotation = transform_tuple_by_matrix(&rotation, &camera->rotation);
	camera->rotation = normalize_vector(&new_rotation);
}

void	camera_reset(t_camera *camera)
{
	camera->location = camera->original_location;
	camera->rotation = camera->original_rotation;
}
