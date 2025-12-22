#include "minirt.h"

t_mat	rotate_x(float x)
{
	t_mat	mat;

	mat = create_identity_matrix(4);
	mat.m[1][1] = cos(x);
	mat.m[2][1] = -sin(x);
	mat.m[1][2] = sin(x);
	mat.m[2][2] = cos(x);
	return (mat);
}

t_mat	rotate_y(float y)
{
	t_mat	mat;

	mat = create_identity_matrix(4);
	mat.m[0][0] = cos(y);
	mat.m[0][2] = sin(y);
	mat.m[2][0] = -sin(y);
	mat.m[2][2] = cos(y);
	return (mat);
}

t_mat	rotate_z(float z)
{
	t_mat	mat;

	mat = create_identity_matrix(4);
	mat.m[0][0] = cos(z);
	mat.m[0][1] = -sin(z);
	mat.m[1][0] = sin(z);
	mat.m[1][1] = cos(z);
	return (mat);
}
