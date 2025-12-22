#include "minirt.h"

t_mat	submatrix(t_mat *mat, int row, int col, int dim)
{
	int		mat_r;
	int		mat_c;
	int		out_r;
	int		out_c;
	float	out[dim - 1][dim - 1];

	out_r = 0;
	mat_r = 0;
	while (mat_r < dim)
	{
		if (mat_r == row)
		{
			mat_r++;
			continue ;
		}
		out_c = 0;
		mat_c = 0;
		while (mat_c < dim)
		{
			if (mat_c == col)
			{
				mat_c++;
				continue ;
			}
			out[out_r][out_c] = mat->m[mat_r][mat_c];
			mat_c++;
			out_c++;
		}
		mat_r++;
		out_r++;
	}
	if (dim == 4)
		return (create_matrix_3(out));
	return (create_matrix_2(out));
}

float	determinant(t_mat *mat, int dim)
{
	t_mat	sub;
	int		col;
	float	sign;
	float	det;
	float	det_term;

	col = 0;
	det = 0.0f;
	sign = 0;
	if (dim == 1)
		return (mat->m[0][0]);
	if (dim == 2)
		return (mat->m[0][0] * mat->m[1][1]
			- mat->m[0][1] * mat->m[1][0]);
	while (col < dim)
	{
		sub = submatrix(mat, 0, col, dim);
		sign = ((0 + col) % 2 == 0) ? 1.0f : -1.0f;
		det_term = determinant(&sub, dim - 1);
		det += sign * mat->m[0][col] * det_term;
		col++;
	}
	return (det);
}

float	cofactor_one_cell(t_mat *mat, int i, int j, int dim)
{
	t_mat	sub;
	float	sign;
	float	c;

	sub = submatrix(mat, i, j, dim);
	c = determinant(&sub, dim - 1);
	sign = ((i + j) % 2 == 0) ? 1.0f : -1.0f;
	return (c * sign);
}

t_mat	invert_matrix(t_mat *mat)
{
	t_mat	inv;
	float	cof;
	float	det;
	int		i;
	int		j;
	int		dim;

	dim = get_matrix_dim(mat, NULL);
	det = determinant(mat, dim);
	inv.type = mat->type;
	i = 0;
	if (is_float_zero(det))
		return (create_identity_matrix(dim));
	while (i < dim)
	{
		j = 0;
		while (j < dim)
		{
			cof = cofactor_one_cell(mat, j, i, dim);
			inv.m[i][j] = cof / det;
			j++;
		}
		i++;
	}
	set_matrix_dim(&inv, dim);
	return (inv);
}
