/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:08:34 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/02 11:43:12 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	prepare_scene(t_system *sys)
{
	int	i;

	camera_transform(&sys->camera);
	init_canvas_dimensions(&sys->camera, WIDTH);
	i = 0;
	while (i < sys->object_count)
	{
		if (sys->obj_list[i].type == SPHERE)
			transform_sphere(&sys->obj_list[i]);
		else if (sys->obj_list[i].type == PLANE)
			transform_plane(&sys->obj_list[i]);
		else if (sys->obj_list[i].type == CYLINDER)
			transform_cylinder(&sys->obj_list[i]);
		i++;
	}
}
