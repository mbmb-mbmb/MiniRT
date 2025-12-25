#include "minirt.h"

t_tuple	reflect(t_tuple *vec, t_tuple *normal)
{
	t_tuple	v_reflected;
	t_tuple	v_temp;
	float	dot;

	dot = dot_product_tuple(vec, normal);
	v_temp = multiply_tuple(normal, 2.0f * dot);
	v_reflected = subtract_tuple(vec, &v_temp);
	return (v_reflected);
}

t_shader_computations	prepare_shading_computitions(t_intersection *hit, t_ray *world_ray)
{
	t_shader_computations	comps;

	comps.point = ray_position(world_ray, hit->t);
	comps.eyev = negate_tuple(&world_ray->direction);
	if (hit->object->type == SPHERE)
		comps.normalv = normal_at(&hit->object->sphere, &comps.point);
	else if (hit->object->type == PLANE)
		comps.normalv = normal_at_plane(&hit->object->plane);
	else if (hit->object->type == CYLINDER)
		comps.normalv = normal_at_cylinder(&hit->object->cylinder, &comps.point);
	comps.inside = false;
	if (dot_product_tuple(&comps.normalv, &comps.eyev) < 0)
	{
		comps.inside = true;
		comps.normalv = negate_tuple(&comps.normalv);
	}
	return (comps);
}

t_tuple	lighting(t_material *material, t_amb_light *amb_light,
				t_spot_light *light, t_shader_computations *comps)
{
	t_tuple	ambient;
	t_tuple	diffuse;
	t_tuple	specular;
	t_tuple	result;

	comps->light_dir = calc_light_direction(&light->location, &comps->point);
	ambient = calculate_ambient(material, amb_light);
	diffuse = calculate_diffuse(material, light, comps);
	specular = calculate_specular(material, light, comps);
	result = add_tuple(&ambient, &diffuse);
	result = add_tuple(&result, &specular);
	result = clamp_tuple(&result, 0.0f, 1.0f);
	return (result);
}
