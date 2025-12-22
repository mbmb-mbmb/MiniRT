#include "minirt.h"

int	get_matrix_dim(t_mat *mat, t_mat *b)
{
	if (b == NULL || (mat->type == b->type))
	{
		if (mat->type == THREE)
			return (3);
		if (mat->type == TWO)
			return (2);
		if (mat->type == FOUR)
			return (4);
	}
	return (-1);
}

t_tuple	row(t_mat *mat, int r)
{
	t_tuple	mat_row;

	mat_row.x = mat->m[r][0];
	mat_row.y = mat->m[r][1];
	mat_row.z = mat->m[r][2];
	mat_row.w = mat->m[r][3];
	return (mat_row);
}

t_tuple	col(t_mat *mat, int c)
{
	t_tuple	mat_col;

	mat_col.x = mat->m[0][c];
	mat_col.y = mat->m[1][c];
	mat_col.z = mat->m[2][c];
	mat_col.w = mat->m[3][c];
	return (mat_col);
}

t_mat	create_identity_matrix(int dim)
{
	t_mat	mat;
	int		i;
	int		j;

	i = 0;
	while (i < dim)
	{
		j = 0;
		while (j < dim)
		{
			if (i == j)
				mat.m[i][j] = 1;
			else
				mat.m[i][j] = 0;
			j++;
		}
		i++;
	}
	set_matrix_dim(&mat, dim);
	return (mat);
}
