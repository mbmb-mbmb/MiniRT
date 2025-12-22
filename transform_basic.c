#include "minirt.h"

t_mat	translation(float x, float y, float z)
{
	t_mat	mat;

	mat = create_identity_matrix(4);
	mat.m[0][3] = x;
	mat.m[1][3] = y;
	mat.m[2][3] = z;
	return (mat);
}

t_mat	scaling(float x, float y, float z)
{
	t_mat	mat;

	mat = create_identity_matrix(4);
	mat.m[0][0] = x;
	mat.m[1][1] = y;
	mat.m[2][2] = z;
	return (mat);
}

t_mat	rotation_from_tuple(t_tuple *angles)
{
	t_mat	rot_x;
	t_mat	rot_y;
	t_mat	rot_z;
	t_mat	rot_temp;

	rot_x = rotate_x(angles->x);
	rot_y = rotate_y(angles->y);
	rot_z = rotate_z(angles->z);
	rot_temp = multiply_matrices(&rot_y, &rot_x);
	return (multiply_matrices(&rot_z, &rot_temp));
}

t_mat	skew(float xy, float xz, float yx, float yz, float zx, float zy)
{
	t_mat	mat;

	mat = create_identity_matrix(4);
	mat.m[0][1] = xy;
	mat.m[0][2] = xz;
	mat.m[1][0] = yx;
	mat.m[1][2] = yz;
	mat.m[2][0] = zx;
	mat.m[2][1] = zy;
	return (mat);
}

void	set_transform(t_object *obj, t_mat *transform)
{
	t_mat	inverse;

	if (obj->type == SPHERE)
	{
		obj->sphere.transform_to_world = *transform;
		inverse = invert_matrix(transform);
		obj->sphere.inv_transform_to_obj = inverse;
		obj->sphere.is_transformed = true;
	}
	else if (obj->type == PLANE)
	{
		obj->plane.transform_to_world = *transform;
		inverse = invert_matrix(transform);
		obj->plane.inv_transform_to_obj = inverse;
		obj->plane.is_transformed = true;
	}
}
