/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:06:50 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/02 11:14:53 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	ray_misses_sphere(float a, float discriminant)
{
	return (fabsf(a) < EPSILON || discriminant < 0.0f);
}

void	intersect_sphere(t_ray *ray, t_intersection_list *list)
{
	float	discriminant;
	t_tuple	origin_to_center;
	float	a;
	float	b;
	float	c;

	origin_to_center = ray->origin;
	origin_to_center.w = VECTOR;
	a = dot_product_tuple(&ray->direction, &ray->direction);
	b = 2 * dot_product_tuple(&ray->direction, &origin_to_center);
	c = dot_product_tuple(&origin_to_center, &origin_to_center) - 1.0f;
	discriminant = b * b - 4 * a * c;
	if (ray_misses_sphere(a, discriminant))
		return ;
	if (list->count < MAX_INTERSECTIONS)
		list->intersections[list->count++].t = (-b - sqrtf(discriminant)) / (2
				* a);
	if (list->count < MAX_INTERSECTIONS)
		list->intersections[list->count++].t = (-b + sqrtf(discriminant)) / (2
				* a);
}

void	intersect_plane(t_ray *ray, t_intersection_list *list)
{
	if (is_float_equal(ray->direction.y, 0.0f))
		return ;
	if (list->count < MAX_INTERSECTIONS)
		list->intersections[list->count++].t = -ray->origin.y
			/ ray->direction.y;
}

t_intersection_list	intersect_world(t_system *sys, t_ray *ray)
{
	t_intersection_list	list;
	t_ray				obj_ray;
	int					i;
	int					previous_count;

	list = (t_intersection_list){0};
	i = 0;
	while (i < sys->object_count)
	{
		obj_ray = ray_to_object_space(ray, &sys->obj_list[i]);
		previous_count = list.count;
		if (sys->obj_list[i].type == SPHERE)
			intersect_sphere(&obj_ray, &list);
		else if (sys->obj_list[i].type == PLANE)
			intersect_plane(&obj_ray, &list);
		else if (sys->obj_list[i].type == CYLINDER)
			intersect_cylinder(&obj_ray, &list);
		while (previous_count < list.count)
			list.intersections[previous_count++].object = &sys->obj_list[i];
		i++;
	}
	return (list);
}

t_intersection	*hit(t_intersection_list *list)
{
	t_intersection	*hit;
	float			closest_t;
	int				i;

	hit = NULL;
	closest_t = FLOAT_MAX;
	i = 0;
	while (i < list->count)
	{
		if (list->intersections[i].t > 0.0f
			&& list->intersections[i].t < closest_t)
		{
			closest_t = list->intersections[i].t;
			hit = &list->intersections[i];
		}
		i++;
	}
	return (hit);
}
