/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:06:28 by mbonsdor          #+#    #+#             */
/*   Updated: 2025/12/26 16:35:22 by mbonsdor         ###   ########.fr       */
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

static void	add_wall_hit(t_ray *ray, t_intersection_list *list, float t)
{
	float	y;

	y = ray->origin.y + t * ray->direction.y;
	if (y > -1.0f && y < 1.0f && list->count < MAX_INTERSECTIONS)
		list->intersections[list->count++].t = t;
}

static void	intersect_cylinder_walls(t_ray *ray, t_intersection_list *list)
{
	float	a;
	float	b;
	float	c;
	float	disc;

	a = ray->direction.x * ray->direction.x + ray->direction.z * ray->direction.z;
	b = 2.0f * (ray->origin.x * ray->direction.x + ray->origin.z * ray->direction.z);
	c = ray->origin.x * ray->origin.x + ray->origin.z * ray->origin.z - 1.0f;
	disc = b * b - 4.0f * a * c;
	if (ray_misses_cylinder(a, disc))
		return ;
	add_wall_hit(ray, list, (-b - sqrtf(disc)) / (2.0f * a));
	add_wall_hit(ray, list, (-b + sqrtf(disc)) / (2.0f * a));
}

static void	intersect_cylinder_caps(t_ray *ray, t_intersection_list *list)
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

void	intersect_cylinder(t_ray *ray, t_intersection_list *list)
{
	intersect_cylinder_walls(ray, list);
	intersect_cylinder_caps(ray, list);
}
