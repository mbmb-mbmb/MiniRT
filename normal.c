#include "minirt.h"

t_tuple	normal_at(t_sphere *sphere, t_tuple *world_point)
{
	t_tuple	object_point;
	t_tuple	object_normal;
	t_tuple	world_normal;
	t_tuple	origin;
	t_mat	transposed_inverse;

	object_point = multiply_matrix_and_tuple(&sphere->inv_transform_to_obj, world_point);
	origin = create_point(0, 0, 0);
	object_normal = subtract_tuple(&object_point, &origin);
	transposed_inverse = transpose_matrix(&sphere->inv_transform_to_obj, 4);
	world_normal = multiply_matrix_and_tuple(&transposed_inverse, &object_normal);
	world_normal.w = VECTOR;
	return (normalize_vector(&world_normal));
}

t_tuple	normal_at_plane(t_plane *plane)
{
	t_tuple	local_normal;
	t_tuple	world_normal;
	t_mat	transposed_inverse;

	local_normal = create_vector(0, 1, 0);
	transposed_inverse = transpose_matrix(&plane->inv_transform_to_obj, 4);
	world_normal = multiply_matrix_and_tuple(&transposed_inverse, &local_normal);
	world_normal.w = VECTOR;
	return (normalize_vector(&world_normal));
}

