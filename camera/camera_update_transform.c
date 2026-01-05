/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_update_transform.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyniemit <jyniemit@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:21:22 by jyniemit          #+#    #+#             */
/*   Updated: 2026/01/05 14:21:25 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	camera_update_transform(t_camera *camera)
{
	t_tuple	from;
	t_tuple	to;
	t_tuple	up;
	t_tuple	camera_obj_origin;

	from = camera->location;
	to = add_tuple(&from, &camera->rotation);
	up = create_vector(0, 1, 0);
	camera->transform = view_transform(&from, &to, &up);
	camera->inverse = invert_matrix(&camera->transform);
	camera_obj_origin = (t_tuple){0.0f, 0.0f, 0.0f, POINT};
	camera->world_origin = transform_tuple_by_matrix(&camera->inverse,
			&camera_obj_origin);
}
