/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:06:43 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/02 11:46:02 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	intersect_plane(t_ray *ray, t_intersection_list *list)
{
	if (is_float_equal(ray->direction.y, 0.0f))
		return ;
	if (list->count < MAX_INTERSECTIONS)
		list->intersections[list->count++].t
			= -ray->origin.y / ray->direction.y;
}
