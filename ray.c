#include "minirt.h"

t_ray	ray_make(t_tuple origin, t_tuple direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

t_tuple	ray_position(t_ray *ray, float t)
{
	t_tuple	v_pos;
	t_tuple	v_dirmult;

	v_dirmult = multiply_tuple(&ray->direction, t);
	v_pos = add_tuple(&ray->origin, &v_dirmult);
	return (v_pos);
}

t_ray	ray_transform(t_ray *ray, t_mat *mat)
{
	t_ray	ray_out;

	ray_out.origin = multiply_matrix_and_tuple(mat, &ray->origin);
	ray_out.direction = multiply_matrix_and_tuple(mat, &ray->direction);
	ray_out.origin.w = POINT;
	ray_out.direction.w = VECTOR;
	return (ray_out);
}

t_ray	ray_to_object_space(t_ray *ray, t_object *obj)
{
	t_ray	obj_ray;

	if (obj->type == SPHERE && obj->sphere.is_transformed)
		obj_ray = ray_transform(ray, &obj->sphere.inv_transform_to_obj);
	else if (obj->type == PLANE && obj->plane.is_transformed)
		obj_ray = ray_transform(ray, &obj->plane.inv_transform_to_obj);
	else
		obj_ray = *ray;
	return (obj_ray);
}
