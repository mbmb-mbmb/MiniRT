#include "../minirt.h"

static t_tuple	find_perp_axis(t_tuple *axis)
{
	if (fabsf(axis->x) < 0.9f)
		return (create_vector(1, 0, 0));
	return (create_vector(0, 0, 1));
}

t_mat	create_rotation_matrix_from_axis(t_tuple *axis)
{
	t_tuple	up;
	t_tuple	arbitrary;
	t_tuple	right;
	t_tuple	forward;
	t_mat	rot;

	up = normalize_vector(axis);
	arbitrary = find_perp_axis(&up);
	right = cross_product_tuple(&arbitrary, &up);
	right = normalize_vector(&right);
	forward = cross_product_tuple(&up, &right);
	rot = create_identity_matrix(4);
	rot.m[0][0] = right.x;
	rot.m[1][0] = right.y;
	rot.m[2][0] = right.z;
	rot.m[0][1] = up.x;
	rot.m[1][1] = up.y;
	rot.m[2][1] = up.z;
	rot.m[0][2] = forward.x;
	rot.m[1][2] = forward.y;
	rot.m[2][2] = forward.z;
	return (rot);
}
