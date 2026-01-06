/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyniemit <jyniemit@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:22:17 by jyniemit          #+#    #+#             */
/*   Updated: 2026/01/05 14:22:17 by jyniemit         ###   ########.fr       */
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
