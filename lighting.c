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
	comps.inside = false;
	return (comps);
}

t_tuple	calculate_ambient(t_material *material, t_amb_light *amb_light)
{
	t_tuple	ambient;
	t_tuple	color;
	t_tuple	with_range;

	color = multiply_tuple_w_tuple(&material->color, &amb_light->color);
	ambient = multiply_tuple(&color, material->ambient);
	with_range = multiply_tuple(&ambient, amb_light->range);
	return (with_range);
}

bool	is_light_behind_surface(t_tuple *light_dir, t_tuple *normal)
{
	return (dot_product_tuple(light_dir, normal) < 0);
}

t_tuple	calculate_diffuse(t_material *material, t_spot_light *light, t_shader_computations *comps)
{
	t_tuple	diffuse;
	t_tuple	color;
	float	scalar;

	if (is_light_behind_surface(&comps->light_dir, &comps->normalv))
		return (create_vector(0, 0, 0));
	color = multiply_tuple_w_tuple(&material->color, &light->color);
	scalar = material->diffuse * light->range
		* dot_product_tuple(&comps->light_dir, &comps->normalv);
	diffuse = multiply_tuple(&color, scalar);
	diffuse.w = 1.0f;
	return (diffuse);
}

t_tuple	calculate_specular(t_material *material, t_spot_light *light, t_shader_computations *comps)
{
	t_tuple	specular;
	t_tuple	neg_lightv;
	t_tuple	reflectv;
	float	factor;

	if (is_light_behind_surface(&comps->light_dir, &comps->normalv))
		return (create_vector(0, 0, 0));
	neg_lightv = negate_tuple(&comps->light_dir);
	reflectv = reflect(&neg_lightv, &comps->normalv);
	if (dot_product_tuple(&reflectv, &comps->eyev) < 0)
		return (create_vector(0, 0, 0));
	factor = powf(dot_product_tuple(&reflectv, &comps->eyev), material->shininess);
	specular = multiply_tuple(&light->color,
					material->specular * light->range * factor);
	specular.w = 1.0f;
	return (specular);
}


t_tuple	calc_light_direction(t_tuple *light_pos, t_tuple *point)
{
	t_tuple	direction;

	direction = subtract_tuple(light_pos, point);
	return (normalize_vector(&direction));
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
