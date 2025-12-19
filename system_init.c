#include "minirt.h"

void	init_system(t_system *sys)
{
	*sys = (t_system){0};
	sys->state = DRAFT_MODE;
	sys->exit_code = 0;
	sys->camera.aspect_ratio = (float)WIDTH / (float)HEIGHT;
}

void	camera_transform(t_camera *camera)
{
	t_tuple	from;
	t_tuple	to;
	t_tuple	up;

	from = camera->location;
	to = add_tuple(&from, &camera->rotation);
	up = create_vector(0, 1, 0);
	camera->transform = view_transform(&from, &to, &up);
	camera->inverse = invert_matrix(&camera->transform);
}

void	setup_sphere_transform(t_object *obj)
{
	t_mat	trans;
	t_mat	scale;
	t_mat	transform;

	trans = translation(obj->sphere.location.x,
						obj->sphere.location.y,
						obj->sphere.location.z);
	scale = scaling(obj->sphere.radius,
					obj->sphere.radius,
					obj->sphere.radius);
	transform = multiply_matrices(&trans, &scale);
	set_transform(obj, &transform);
}

void	transform_plane(t_object *obj)
{
	t_mat	world_location;
	t_mat	rotation;
	t_mat	transform;

	world_location = translation(obj->plane.location.x,
								 obj->plane.location.y,
								 obj->plane.location.z);
	rotation = rotation_from_tuple(&obj->plane.rotation);
	transform = multiply_matrices(&world_location, &rotation);
	set_transform(obj, &transform);
}

void	prepare_scene(t_system *sys)
{
	int	i;

	camera_transform(&sys->camera);
	i = 0;
	while (i < sys->object_count)
	{
		if (sys->obj_list[i].type == SPHERE)
			setup_sphere_transform(&sys->obj_list[i]);
		else if (sys->obj_list[i].type == PLANE)
			transform_plane(&sys->obj_list[i]);
		i++;
	}
}
