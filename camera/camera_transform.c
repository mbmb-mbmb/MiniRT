/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_transform.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:08:34 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/02 11:43:12 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	camera_transform(t_camera *camera)
{
	camera_update_transform(camera);
	camera->original_location = camera->location;
	camera->original_rotation = camera->rotation;
}
