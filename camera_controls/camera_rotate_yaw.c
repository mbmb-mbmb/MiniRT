/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_rotate_yaw.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyniemit <jyniemit@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:22:12 by jyniemit          #+#    #+#             */
/*   Updated: 2026/01/05 14:22:12 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	camera_rotate_yaw(t_camera *camera, float angle)
{
	t_mat	rotation;
	t_tuple	new_rotation;

	rotation = rotate_y(angle);
	new_rotation = transform_tuple_by_matrix(&rotation, &camera->rotation);
	camera->rotation = normalize_vector(&new_rotation);
}
