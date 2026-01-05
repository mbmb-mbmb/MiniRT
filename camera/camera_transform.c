/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyniemit <jyniemit@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:21:05 by jyniemit          #+#    #+#             */
/*   Updated: 2026/01/05 14:21:13 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	camera_transform(t_camera *camera)
{
	camera_update_transform(camera);
	camera->original_location = camera->location;
	camera->original_rotation = camera->rotation;
}
