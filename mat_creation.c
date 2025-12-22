#include "minirt.h"

bool	matrices_are_equal(t_mat *a, t_mat *b)
{
	int		row;
	int		col;
	int		dim;

	dim = get_matrix_dim(a, b);
	if (dim == -1)
		return (false);
	row = 0;
	while (row < dim)
	{
		col = 0;
		while (col < dim)
		{
			if (!is_float_equal(a->m[row][col], b->m[row][col]))
				return (false);
			col++;
		}
		row++;
	}
	return (true);
}

t_mat	create_matrix_2(float m[2][2])
{
	t_mat	matrix;

	matrix = (t_mat){};
	matrix.type = TWO;
	matrix.m[0][0] = m[0][0];
	matrix.m[0][1] = m[0][1];
	matrix.m[1][0] = m[1][0];
	matrix.m[1][1] = m[1][1];
	return (matrix);
}

t_mat	create_matrix_3(float m[3][3])
{
	t_mat	matrix;

	matrix = (t_mat){};
	matrix.type = THREE;
	matrix.m[0][0] = m[0][0];
	matrix.m[0][1] = m[0][1];
	matrix.m[0][2] = m[0][2];
	matrix.m[1][0] = m[1][0];
	matrix.m[1][1] = m[1][1];
	matrix.m[1][2] = m[1][2];
	matrix.m[2][0] = m[2][0];
	matrix.m[2][1] = m[2][1];
	matrix.m[2][2] = m[2][2];
	return (matrix);
}
