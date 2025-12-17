#include "minirt.h"

t_mat	build_orientation_from_view(t_tuple *eye, t_tuple *target, t_tuple *up)
{
	t_tuple	forward;
	t_tuple	upn;
	t_tuple	left;
	t_tuple	true_up;
	t_mat	orientation;

	forward = subtract_tuple(target, eye);
	forward = normalize_vector(&forward);
	upn = normalize_vector(up);
	left = cross_product_tuple(&forward, &upn);
	true_up = cross_product_tuple(&left, &forward);
	orientation = create_identity_matrix(4);
	orientation.m[0][0] = left.x;
	orientation.m[0][1] = left.y;
	orientation.m[0][2] = left.z;
	orientation.m[1][0] = true_up.x;
	orientation.m[1][1] = true_up.y;
	orientation.m[1][2] = true_up.z;
	orientation.m[2][0] = -forward.x;
	orientation.m[2][1] = -forward.y;
	orientation.m[2][2] = -forward.z;
	set_matrix_dim(&orientation, 4);
	return (orientation);
}

t_mat	view_transform(t_tuple *eye, t_tuple *target, t_tuple *up)
{
	t_mat	orientation;
	t_mat	translate;

	orientation = build_orientation_from_view(eye, target, up);
	translate = translation(-eye->x, -eye->y, -eye->z);
	return (multiply_matrices(&orientation, &translate));
}

t_tuple	compute_pixel_on_canvas(t_camera *camera, uint32_t x, uint32_t y)
{
	float	half_view;
	float	half_width;
	float	half_height;
	float	pixel_size;
	float	world_x;
	float	world_y;

	half_view = tanf(degrees_to_radians((float)camera->fov) / 2.0f);
	if (camera->aspect_ratio >= 1.0f)
	{
		half_width = half_view;
		half_height = half_view / camera->aspect_ratio;
	}
	else
	{
		half_width = half_view * camera->aspect_ratio;
		half_height = half_view;
	}
	pixel_size = (half_width * 2.0f) / (float)WIDTH;
	world_x = half_width - ((float)x + 0.5f) * pixel_size;
	world_y = half_height - ((float)y + 0.5f) * pixel_size;
	return (create_point(world_x, world_y, -1.0f));
}

t_ray	ray_for_pixel(t_camera *camera, uint32_t x, uint32_t y)
{
	t_ray	ray;
	t_tuple	pixel_on_canvas;
	t_tuple	pixel_in_world;
	t_tuple	camera_obj_origin;
	t_tuple	origin_in_world;
	t_tuple	direction;

	pixel_on_canvas = compute_pixel_on_canvas(camera, x, y);
	pixel_in_world = multiply_matrix_and_tuple(&camera->inverse, &pixel_on_canvas);
	camera_obj_origin = (t_tuple){0.0f, 0.0f, 0.0f, POINT};
	origin_in_world = multiply_matrix_and_tuple(&camera->inverse, &camera_obj_origin);
	direction = subtract_tuple(&pixel_in_world, &origin_in_world);
	ray.origin = origin_in_world;
	ray.direction = normalize_vector(&direction);
	return (ray);
}
