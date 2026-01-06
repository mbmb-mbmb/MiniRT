/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyniemit <jyniemit@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:54:28 by jyniemit          #+#    #+#             */
/*   Updated: 2026/01/05 15:54:28 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	set_transform(t_object *obj, t_mat *transform)
{
	if (obj->type == SPHERE)
	{
		obj->sphere.transform_to_world = *transform;
		obj->sphere.inv_transform_to_obj = invert_matrix(transform);
		obj->sphere.is_transformed = true;
		obj->flags |= OBJ_HAS_TRANSFORM;
	}
	else if (obj->type == PLANE)
	{
		obj->plane.transform_to_world = *transform;
		obj->plane.inv_transform_to_obj = invert_matrix(transform);
		obj->plane.is_transformed = true;
		obj->flags |= OBJ_HAS_TRANSFORM;
	}
	else if (obj->type == CYLINDER)
	{
		obj->cylinder.transform_to_world = *transform;
		obj->cylinder.inv_transform_to_obj = invert_matrix(transform);
		obj->cylinder.is_transformed = true;
		obj->flags |= OBJ_HAS_TRANSFORM;
	}
}
