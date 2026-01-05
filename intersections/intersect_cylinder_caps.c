/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder_caps.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:06:28 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/02 11:45:23 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	intersect_cylinder_caps(t_ray *ray, t_intersection_list *list)
{
	float	t;
	float	x;
	float	z;

	if (ray_parallel_to_y(ray))
		return ;
	t = (-1.0f - ray->origin.y) / ray->direction.y;
	if (t > 0.0f && list->count < MAX_INTERSECTIONS)
	{
		x = ray->origin.x + t * ray->direction.x;
		z = ray->origin.z + t * ray->direction.z;
		if (x * x + z * z <= 1.0f)
			list->intersections[list->count++].t = t;
	}
	t = (1.0f - ray->origin.y) / ray->direction.y;
	if (t > 0.0f && list->count < MAX_INTERSECTIONS)
	{
		x = ray->origin.x + t * ray->direction.x;
		z = ray->origin.z + t * ray->direction.z;
		if (x * x + z * z <= 1.0f)
			list->intersections[list->count++].t = t;
	}
}
