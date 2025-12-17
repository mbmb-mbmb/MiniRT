#include "minirt.h"

void	set_matrix_dim(t_mat *mat, int dim)
{
	if (dim == 3)
		mat->type = THREE;
	else if (dim == 2)
		mat->type = TWO;
	else if (dim == 4)
		mat->type = FOUR;
	else
		mat->type = -1;
}

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

t_mat	transpose_matrix(t_mat *mat, int dim)
{
	int		i;
	int		j;
	t_mat	mat_trans;

	mat_trans.type = mat->type;
	i = 0;
	while (i < dim)
	{
		j = 0;
		while (j < dim)
		{
			mat_trans.m[j][i] = mat->m[i][j];
			j++;
		}
		i++;
	}
	return (mat_trans);
}

t_mat	multiply_matrices(t_mat *ina, t_mat *inb)
{
	t_mat	out;
	int		i;
	int		j;
	t_tuple	row_result;
	t_tuple	col_result;

	out = (t_mat){0};
	out.type = ina->type;
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			row_result = row(ina, i);
			col_result = col(inb, j);
			out.m[i][j] = dot_product_tuple_naive(&row_result, &col_result);
			j++;
		}
		i++;
	}
	return (out);
}

t_tuple	multiply_matrix_and_tuple(t_mat *mat, t_tuple *tup_in)
{
	int		i;
	t_tuple	tup_out;
	t_tuple	row_result;

	i = 0;
	while (i < 4)
	{
		row_result = row(mat, i);
		if (i == 0)
			tup_out.x = dot_product_tuple_naive(&row_result, tup_in);
		else if (i == 1)
			tup_out.y = dot_product_tuple_naive(&row_result, tup_in);
		else if (i == 2)
			tup_out.z = dot_product_tuple_naive(&row_result, tup_in);
		else if (i == 3)
			tup_out.w = dot_product_tuple_naive(&row_result, tup_in);
		i++;
	}
	return (tup_out);
}
