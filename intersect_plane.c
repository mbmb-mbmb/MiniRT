#include "minirt.h"

/*
 * Computes the intersection of a ray with an infinite plane.
 * The plane is at y=0 with normal pointing up (0,1,0) in object space.
 * Returns empty list if ray is parallel to plane.
 */
t_intersection_list	intersect_plane(t_ray *ray)
{
	t_intersection_list	intersections;

	intersections.count = 0;
	if (is_float_equal(ray->direction.y, 0.0f))
		return (intersections);
	intersections.intersections[0].t = -ray->origin.y / ray->direction.y;
	intersections.count = 1;
	return (intersections);
}
