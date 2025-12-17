#include "minirt.h"

t_tuple	color_at(t_system *sys, t_ray *ray)
{
	t_intersection_list	intersections;
	t_shader_computations	comps;
	t_intersection		*closest_hit;
	t_tuple				color;

	intersections = intersect_world(sys, ray);
	closest_hit = hit(&intersections);
	if (closest_hit == NULL)
		return (create_vector(0, 0, 0));
	comps = prepare_shading_computitions(closest_hit, ray);
	color = lighting(&closest_hit->object->sphere.material,
				&sys->amb_light,
				&sys->light_list[0],
				&comps);
	color.w = 1.0f;
	return (color);
}

void	render(t_system *sys, mlx_image_t *img)
{
	int		x;
	int		y;
	t_ray	ray;
	t_tuple	color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = ray_for_pixel(&sys->camera, (uint32_t)x, (uint32_t)y);
			color = color_at(sys, &ray);
			mlx_put_pixel(img, x, y, tuple_to_rgba(&color));
			x++;
		}
		y++;
	}
}
