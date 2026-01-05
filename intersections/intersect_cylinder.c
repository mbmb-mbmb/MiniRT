/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:06:28 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/02 11:45:23 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

bool	ray_misses_cylinder(float a, float discriminant)
{
	return (fabsf(a) < EPSILON || discriminant < 0.0f);
}

bool	ray_parallel_to_y(t_ray *ray)
{
	return (fabsf(ray->direction.y) < EPSILON);
}

void	intersect_cylinder(t_ray *ray, t_intersection_list *list)
{
	intersect_cylinder_walls(ray, list);
	intersect_cylinder_caps(ray, list);
}
