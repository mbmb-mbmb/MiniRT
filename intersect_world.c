#include "minirt.h"

void	append_intersections(t_intersection_list *dest, t_intersection_list *src)
{
	int	i;

	i = 0;
	while (i < src->count && dest->count < MAX_INTERSECTIONS)
	{
		dest->intersections[dest->count] = src->intersections[i];
		dest->count++;
		i++;
	}
}

void	tag_intersections(t_intersection_list *intersections, t_object *object)
{
	int	i;

	i = 0;
	while (i < intersections->count)
	{
		intersections->intersections[i].object = object;
		i++;
	}
}

t_intersection_list	intersect_world(t_system *sys, t_ray *ray)
{
	t_intersection_list	obj_intrs;
	t_intersection_list	all_intrs;
	t_ray				obj_ray;
	int				i;

	all_intrs = (t_intersection_list){0};
	all_intrs.count = 0;
	i = 0;
	while (i < sys->object_count)
	{
		obj_intrs.count = 0;
		obj_ray = ray_to_object_space(ray, &sys->obj_list[i]);
		if (sys->obj_list[i].type == SPHERE)
			obj_intrs = intersect_sphere(&sys->obj_list[i].sphere, &obj_ray);
		else if (sys->obj_list[i].type == PLANE)
			obj_intrs = intersect_plane(&obj_ray);
		else if (sys->obj_list[i].type == CYLINDER)
			obj_intrs = intersect_cylinder(&sys->obj_list[i].cylinder, &obj_ray);
		tag_intersections(&obj_intrs, &sys->obj_list[i]);
		append_intersections(&all_intrs, &obj_intrs);
		i++;
	}
	return (all_intrs);
}

t_intersection	*hit(t_intersection_list *intersections)
{
	t_intersection	*hit;
	float			closest_t;
	int				i;

	hit = NULL;
	closest_t = FLOAT_MAX;
	i = 0;
	while (i < intersections->count)
	{
		if (intersections->intersections[i].t > 0.0f
			&& intersections->intersections[i].t < closest_t)
		{
			closest_t = intersections->intersections[i].t;
			hit = &intersections->intersections[i];
		}
		i++;
	}
	return (hit);
}
