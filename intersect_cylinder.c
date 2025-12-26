/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:06:28 by mbonsdor          #+#    #+#             */
/*   Updated: 2025/12/26 16:06:29 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	ray_misses_cylinder(float a, float discriminant)
{
	return (fabsf(a) < EPSILON || discriminant < 0.0f);
}

static bool	ray_parallel_to_y(t_ray *ray)
{
	return (fabsf(ray->direction.y) < EPSILON);
}

static void	intersect_cylinder_caps(t_ray *ray, t_intersection_list *inters)
{
	float	t;
	float	x;
	float	z;

	if (ray_parallel_to_y(ray))
		return ;
	t = (-1.0f - ray->origin.y) / ray->direction.y;
	if (t > 0.0f && inters->count < MAX_INTERSECTIONS)
	{
		x = ray->origin.x + t * ray->direction.x;
		z = ray->origin.z + t * ray->direction.z;
		if (x * x + z * z <= 1.0f)
			inters->intersections[inters->count++].t = t;
	}
	t = (1.0f - ray->origin.y) / ray->direction.y;
	if (t > 0.0f && inters->count < MAX_INTERSECTIONS)
	{
		x = ray->origin.x + t * ray->direction.x;
		z = ray->origin.z + t * ray->direction.z;
		if (x * x + z * z <= 1.0f)
			inters->intersections[inters->count++].t = t;
	}
}

t_intersection_list	intersect_cylinder(t_cylinder *cylinder, t_ray *ray)
{
	t_intersection_list	intersections;
	float				discriminant;
	float				a;
	float				b;
	float				c;
	float				y;
	float				t0;
	float				t1;

	(void)cylinder;
	intersections = (t_intersection_list){0};
	intersections.count = 0;
	a = ray->direction.x * ray->direction.x + ray->direction.z * ray->direction.z;
	b = 2.0f * (ray->origin.x * ray->direction.x + ray->origin.z * ray->direction.z);
	c = ray->origin.x * ray->origin.x + ray->origin.z * ray->origin.z - 1.0f;
	discriminant = b * b - 4.0f * a * c;
	if (ray_misses_cylinder(a, discriminant))
	{
		intersect_cylinder_caps(ray, &intersections);
		return (intersections);
	}
	t0 = (-b - sqrtf(discriminant)) / (2.0f * a);
	y = ray->origin.y + t0 * ray->direction.y;
	if (y > -1.0f && y < 1.0f && intersections.count < MAX_INTERSECTIONS)
		intersections.intersections[intersections.count++].t = t0;
	t1 = (-b + sqrtf(discriminant)) / (2.0f * a);
	y = ray->origin.y + t1 * ray->direction.y;
	if (y > -1.0f && y < 1.0f && intersections.count < MAX_INTERSECTIONS)
		intersections.intersections[intersections.count++].t = t1;
	intersect_cylinder_caps(ray, &intersections);
	return (intersections);
}


