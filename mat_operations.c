#include "minirt.h"

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
