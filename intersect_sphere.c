/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:06:50 by mbonsdor          #+#    #+#             */
/*   Updated: 2025/12/26 16:06:51 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	ray_misses_sphere(float a, float discriminant)
{
	return (fabsf(a) < EPSILON || discriminant < 0.0f);
}

void	intersect_sphere(t_ray *ray, t_intersection_list *list)
{
	float				discriminant;
	t_tuple				origin_to_center;
	float				a;
	float				b;
	float				c;

	origin_to_center = ray->origin;
	origin_to_center.w = VECTOR;
	a = dot_product_tuple(&ray->direction, &ray->direction);
	b = 2 * dot_product_tuple(&ray->direction, &origin_to_center);
	c = dot_product_tuple(&origin_to_center, &origin_to_center) - 1.0f;
	discriminant = b * b - 4 * a * c;
	if (ray_misses_sphere(a, discriminant))
		return ;
	if (list->count < MAX_INTERSECTIONS)
		list->intersections[list->count++].t = (-b - sqrtf(discriminant)) / (2 * a);
	if (list->count < MAX_INTERSECTIONS)
		list->intersections[list->count++].t = (-b + sqrtf(discriminant)) / (2 * a);
}
