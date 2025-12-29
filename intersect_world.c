/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_world.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:06:56 by mbonsdor          #+#    #+#             */
/*   Updated: 2025/12/26 16:06:57 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
