/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:06:43 by mbonsdor          #+#    #+#             */
/*   Updated: 2025/12/26 16:06:44 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 * Computes the intersection of a ray with an infinite plane.
 * The plane is at y=0 with normal pointing up (0,1,0) in object space.
 * Returns empty list if ray is parallel to plane.
 */
void	intersect_plane(t_ray *ray, t_intersection_list *list)
{
	if (is_float_equal(ray->direction.y, 0.0f))
		return ;
	if (list->count < MAX_INTERSECTIONS)
		list->intersections[list->count++].t = -ray->origin.y / ray->direction.y;
}
