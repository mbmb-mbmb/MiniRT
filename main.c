#include "minirt.h"

static void	ft_error(int error_code)
{
	exit(error_code);
}

/* DEBUGGING FUNCTIONS */
void	print_matrix(t_mat *M)
{
	printf("%f %f %f %f\n", M->m[0][0], M->m[0][1], M->m[0][2], M->m[0][3]);
	printf("%f %f %f %f\n", M->m[1][0], M->m[1][1], M->m[1][2], M->m[1][3]);
	printf("%f %f %f %f\n", M->m[2][0], M->m[2][1], M->m[2][2], M->m[2][3]);
	printf("%f %f %f %f\n", M->m[3][0], M->m[3][1], M->m[3][2], M->m[3][3]);
}

t_mat	test_matrix_4(void)
{
	t_mat	M;

	M = (t_mat){};
	M.type = FOUR;
		M.m[0][0] = 1;
		M.m[0][1] = 2;
		M.m[0][2] = 3;
		M.m[0][3] = 4;

		M.m[1][0] = 0;
		M.m[1][1] = 1;
		M.m[1][2] = 2;
		M.m[1][3] = 3;

		M.m[2][0] = 1;
		M.m[2][1] = 0;
		M.m[2][2] = 1;
		M.m[2][3] = 2;

		M.m[3][0] = 2;
		M.m[3][1] = 1;
		M.m[3][2] = 0;
		M.m[3][3] = 1;
	return (M);
}
void	print_tuple(t_tuple *T)
{
	printf("T: %f, %f, %f, %f\n", T->x, T->y, T->z, T->w);
}

/* END DEBUGGING FUNCTIONS */

static void	init_system(t_system *sys)
{
	*sys = (t_system){0};
	sys->state = DRAFT_MODE;
	sys->exit_code = 0;
}

static void	draft_transformations(t_system *sys)
{
	(void)sys;
}

static void	render_scene(t_system *sys, mlx_image_t *img)
{
	uint32_t	color;
	int			x;
	int			y;

	y = 0;
	color = sys->amb_light.rgb;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
			mlx_put_pixel(img, ++x, y, color);
		++y;
	}
	sys->state |= RENDER_COMPLETE;
}

static int	cleanup(t_system *sys)
{
	return (sys->exit_code);
}

static void	frame(void *param)
{
	t_app		*app;
	t_system	*system;

	app = (t_app *)param;
	system = &app->system;
	if (mlx_is_key_down(app->mlx, MLX_KEY_ESCAPE))
		system->state |= SHOULD_EXIT;
	if (!(system->state & SHOULD_EXIT))
	{
		if (system->state & DRAFT_MODE)
			draft_transformations(system);
		if (!(system->state & RENDER_COMPLETE))
			render_scene(system, app->img);
	}
	else
	{
		mlx_close_window(app->mlx);
	}
}

float	degrees_to_radians(float degrees)
{
	return (degrees * M_PI / 180.0);
}

float	radians_to_degrees(float radians)
{
	return (radians * 180.0 / M_PI);
}

t_tuple	create_point(float x, float y, float z)
{
	t_tuple	point;

	point.w = POINT;
	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

t_tuple	create_vector(float x, float y, float z)
{
	t_tuple	vector;

	vector.w = VECTOR;
	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}

bool	is_float_equal(float a, float b)
{
	return (fabsf(a - b) < EPSILON);
}

static int	classify_w(const t_tuple *t)
{
	if (is_float_equal(t->w, 0.0f))
		return (VECTOR);
	if (is_float_equal(t->w, 1.0f))
		return (POINT);
	return (TUPLE_INCORRECT);
}

static float	canonical_w(int kind)
{
	if (kind == VECTOR)
		return (0.0f);
	if (kind == POINT)
		return (1.0f);
	return ((float)TUPLE_INCORRECT);
}

static int	add_kind(int ak, int bk)
{
	if (ak == POINT && bk == POINT)
		return (TUPLE_INCORRECT);
	return (ak | bk);
}

static int	sub_kind(int ak, int bk)
{
	if (ak == VECTOR && bk == POINT)
		return (TUPLE_INCORRECT);
	return (ak ^ bk);
}

bool	is_tuple_equal(const t_tuple *a, const t_tuple *b)
{
	return (is_float_equal(a->w, b->w) && is_float_equal(a->x, b->x)
		&& is_float_equal(a->z, b->z) && is_float_equal(a->y, b->y));
}

t_tuple	add_tuple(const t_tuple *a, const t_tuple *b)
{
	t_tuple	result;
	int		ak;
	int		bk;
	int		rk;

	ak = classify_w(a);
	bk = classify_w(b);
	rk = add_kind(ak, bk);
	result = (t_tuple){};
	result.x = a->x + b->x;
	result.y = a->y + b->y;
	result.z = a->z + b->z;
	result.w = canonical_w(rk);
	return (result);
}

t_tuple	subtract_tuple(const t_tuple *a, const t_tuple *b)
{
	t_tuple	result;
	int		ak;
	int		bk;
	int		rk;

	ak = classify_w(a);
	bk = classify_w(b);
	rk = sub_kind(ak, bk);
	result = (t_tuple){};
	result.x = a->x - b->x;
	result.y = a->y - b->y;
	result.z = a->z - b->z;
	result.w = canonical_w(rk);
	return (result);
}

t_tuple	negate_tuple(const t_tuple *a)
{
	t_tuple	result;

	result.x = a->x * -1;
	result.y = a->y * -1;
	result.z = a->z * -1;
	result.w = a->w;
	return (result);
}

t_tuple	multiply_tuple(t_tuple *a, float mult)
{
	t_tuple	result;

	result = (t_tuple){.x = a->x * mult, .y = a->y * mult, .z = a->z * mult,
		.w = a->w};
	return (result);
}

t_tuple	divide_tuple(t_tuple *a, float div)
{
	t_tuple	result;

	result = (t_tuple){};
	result.w = TUPLE_INCORRECT;
	if (fabsf(div) < EPSILON)
		return (result);
	result = (t_tuple){.x = a->x / div, .y = a->y / div, .z = a->z / div,
		.w = a->w};
	return (result);
}

float	magnitude_tuple(t_tuple *a)
{
	return (sqrtf(a->x * a->x + a->y * a->y + a->z * a->z));
}

t_tuple	normalize_tuple(t_tuple *a)
{
	float	mag;
	t_tuple	result;
	int		ak;

	result = (t_tuple){};
	result.w = TUPLE_INCORRECT;
	ak = classify_w(a);
	if (ak != VECTOR)
		return (result);
	mag = magnitude_tuple(a);
	if (mag < EPSILON)
		return (result);
	result = (t_tuple){.x = a->x / mag, .y = a->y / mag, .z = a->z / mag,
		.w = VECTOR};
	return (result);
}

float	dot_product_tuple(t_tuple *a, t_tuple *b)
{
	int	ak;
	int	bk;

	ak = classify_w(a);
	bk = classify_w(b);
	if (ak != VECTOR || bk != VECTOR)
		return (0.0f);
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

float	dot_product_tuple_naive(t_tuple *a, t_tuple *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z + a->w * b->w);
}

t_tuple	cross_product_tuple(t_tuple *a, t_tuple *b)
{
	t_tuple	result;
	int		ak;
	int		bk;

	result = (t_tuple){};
	result.w = TUPLE_INCORRECT;
	ak = classify_w(a);
	bk = classify_w(b);
	if (ak != VECTOR || bk != VECTOR)
		return (result);
	result = (t_tuple){.x = a->y * b->z - a->z * b->y, .y = a->z * b->x - a->x
		* b->z, .z = a->x * b->y - a->y * b->x, .w = VECTOR};
	return (result);
}

t_tuple create_color(float red, float green, float blue, float alpha)
{
	t_tuple result;
	result = (t_tuple){ .x = red, .y = green, .z = blue, .w = alpha};
	return (result);
}

// t_mat create_matrix_4(float m[4][4])
// {
// 	t_mat	matrix;

// 	matrix.type = FOUR;
// 	matrix.m[0] = *m[0];
// 	matrix.m[1] = *m[1];
// 	matrix.m[2] = *m[2];
// 	matrix.m[3] = *m[3];
// 	return (matrix);
// }

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
int	get_matrix_dim(t_mat *M, t_mat *B)
{
	if (B == NULL || (M->type == B->type))
	{
		if (M->type == THREE)
			return (3);
		if (M->type == TWO)
			return (2);
		if (M->type == FOUR)
			return (4);
	}
	return (-1);
}

void	set_matrix_dim(t_mat *M, int dim)
{
	if (dim == 3)
		M->type = THREE;
	else if (dim == 2)
		M->type = TWO;
	else if (dim == 4)
		M->type = FOUR;
	else
		M->type = -1;
}

t_mat	create_identity_matrix(int dim)
{
	t_mat	M;
	int		i;
	int		j;

	i = 0;
	while(i < dim)
	{
		j = 0;
		while(j < dim)
		{
			if (i == j)
				M.m[i][j] = 1;
			else
				M.m[i][j] = 0;
			j++;
		}
		i++;
	}
	set_matrix_dim(&M, dim);
	return (M);
}


bool	matrices_are_equal(t_mat *A, t_mat *B)
{
	int	i;
	int	j;
	int	dim;

	dim = get_matrix_dim(A, B);
	if (dim == -1)
		return (false);
	i = 0;
	while(i < dim)
	{
		j = 0;
		while(j < dim)
		{
			if(A->m[i][j] != B->m[i][j])
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

t_tuple	row(t_mat *M, int row)
{
	t_tuple	M_row;

	M_row.w = M->m[row][0];
	M_row.x = M->m[row][1];
	M_row.y = M->m[row][2];
	M_row.z = M->m[row][3];
	return (M_row);
}

t_tuple	col(t_mat *M, int col)
{
	t_tuple	M_col;

	M_col.w = M->m[0][col];
	M_col.x = M->m[1][col];
	M_col.y = M->m[2][col];
	M_col.z = M->m[3][col];
	return (M_col);
}

t_mat	multiply_matrices(t_mat *A, t_mat *B)
{
	t_mat	M;
	int		i;
	int		j;
	t_tuple	roow;
	t_tuple	cool;

	i = 0;
	while(i < 4)
	{
		j = 0;
		while(j < 4)
		{
			roow = row(A, i);
			cool = col(B, j);
			M.m[i][j] = dot_product_tuple_naive(&roow, &cool);
			j++;
		}
		i++;
	}
	return (M);
}

t_tuple	multiply_matrix_and_tuple(t_mat *A, t_tuple *tup)
{
	int		i;
	t_tuple	T;
	t_tuple	roow;

	i = 0;
	while(i < 4)
	{
		roow = row(A, i);
		if (i == 0)
			T.x = dot_product_tuple_naive(&roow, tup);
		else if (i == 1)
			T.y = dot_product_tuple_naive(&roow, tup);
		else if (i == 2)
			T.z = dot_product_tuple_naive(&roow, tup);
		else if (i == 3)
			T.w = dot_product_tuple_naive(&roow, tup);
		i++;
	}
	return (T);
}

t_mat	transpose_matrix(t_mat *M, int dim)
{
	int		i;
	int		j;
	int		temp[dim][dim];
	t_mat	M_trans;

	M_trans.type = M->type;
	i = 0;
	while(i < dim)
	{
		j = 0;
		while(j < dim)
		{
			temp[i][j] = M->m[i][j];
			M_trans.m[i][j] = M->m[j][i];
			M_trans.m[j][i] = temp[i][j];
			j++;
		}
		i++;
	}
	return (M_trans);
}

t_mat	submatrix(t_mat *M, int row, int col, int dim)
{
	int		i_M;
	int		j_M;
	int		i_out;
	int		j_out;
	float	out[dim-1][dim-1];


	i_out = 0;
	i_M = 0;
	while(i_M < dim)
	{
		if (i_M == row)
		{
			i_M++;
			continue ;
		}
		j_out = 0;
		j_M = 0;
		while(j_M < dim)
		{
			if( j_M == col)
			{
				j_M++;
				continue ;
			}
			out[i_out][j_out] = M->m[i_M][j_M];
			j_M++;
			j_out++;
		}
		i_M++;
		i_out++;
	}
	if (dim == 4)
		return (create_matrix_3(out));
	else
		return (create_matrix_2(out));
}

float	determinant(t_mat *M, int dim)
{
	t_mat	M_sub;
	int		col;
	int		sign;
	float	det;
	float	det_temp;

	col = 0;
	det = 0.0f;
	sign = 0;
	if (dim == 1)
		return (M->m[0][0]);
	if (dim == 2)
		return (M->m[0][0] * M->m[1][1] - M->m[0][1] * M->m[1][0]);
	while (col < dim)
	{
		M_sub = submatrix(M, 0, col, dim);
		if ((0 + col) % 2 == 0)
			sign = 1;
		else
		 	sign = -1;
		det_temp = determinant(&M_sub, dim - 1);
		det += sign * M->m[0][col] * det_temp;
		col++;
	}
	return (det);
}

float	cofactor_one_cell(t_mat *M, int i, int j, int dim)
{
	t_mat	M_sub;
	int		sign;
	float	c;

	M_sub = submatrix(M, i, j, dim);
	c = determinant(&M_sub, dim - 1);
	if ((i + j) % 2 == 0)
		sign = 1;
	else
		sign = -1;
	return(c * sign);
}

t_mat	cofactor_matrix(t_mat *M)
{
	t_mat	M_out;
	int		i;
	int		j;
	int		dim;

	i = 0;
	dim = get_matrix_dim(M, NULL);
	while(i < dim)
	{
		j = 0;
		while(j < dim)
		{
			M_out.m[i][j] = cofactor_one_cell(M, i, j, dim);
			j++;
		}
		i++;
	}
	return (M_out);
}

bool	is_matrix_invertible(t_mat *M)
{
	if(determinant(M, get_matrix_dim(M, NULL)) == 0)
		return (false);
	return (true);
}

t_mat	invert_matrix(t_mat *M)
{
	t_mat	M_inv;
	float	c;
	float	d;
	int		i;
	int		j;
	int		dim;

	dim = get_matrix_dim(M, NULL);
	d = determinant(M, dim);
	i = 0;
	if (!is_matrix_invertible(M))
		return (create_identity_matrix(4));
	while(i < dim)
	{
		j = 0;
		while(j < dim)
		{
			c = cofactor_one_cell(M, j, i, dim);
			M_inv.m[i][j] = c / d;
			j++;
		}
		i++;
	}
	return (M_inv);
}

t_mat	translation(float x, float y, float z)
{
	t_mat	M;

	M = create_identity_matrix(4);
	M.m[0][3] = x;
	M.m[1][3] = y;
	M.m[2][3] = z;
	return (M);
}

t_mat	scaling(float x, float y, float z)
{
	t_mat	M;

	M = create_identity_matrix(4);
	M.m[0][0] = x;
	M.m[1][1] = y;
	M.m[2][2] = z;
	return (M);
}

t_mat	rotate_x(float x)
{
	t_mat	M;

	M = create_identity_matrix(4);
	M.m[1][1] = cos(x);
	M.m[2][1] = -sin(x);
	M.m[1][2] = sin(x);    
	M.m[2][2] = cos(x);
	return (M);
}

t_mat	rotate_y(float y)
{
	t_mat	M;

	M = create_identity_matrix(4);
	M.m[0][0] = cos(y);
	M.m[0][2] = sin(y);
	M.m[2][0] = -sin(y);    
	M.m[2][2] = cos(y);
	return (M);
}

t_mat	rotate_z(float z)
{
	t_mat	M;

	M = create_identity_matrix(4);
	M.m[0][0] = cos(z);
	M.m[0][1] = -sin(z);
	M.m[1][0] = sin(z);    
	M.m[1][1] = cos(z);
	return (M);
}

t_mat	skew(float xy, float xz, float yx, float yz, float zx, float zy)
{
    t_mat	M;

	M = create_identity_matrix(4);
	M.m[0][1] = xy;
	M.m[0][2] = xz;
	M.m[1][0] = yx;
	M.m[1][2] = yz;
	M.m[2][0] = zx;
	M.m[2][1] = zy;
	return (M);
}

int	main(int argc, char **av)
{
	t_app	app;
	int		code;

	app = (t_app){};
	app.system = (t_system){};
	if (argc != 2)
		ft_error(1);
	init_system(&app.system);
	rt_parser(av[1], &app.system);
	app.mlx = mlx_init(WIDTH, HEIGHT, "MiniRT", true);
	if (!app.mlx)
		ft_error(1);
	app.img = mlx_new_image(app.mlx, WIDTH, HEIGHT);
	if (!app.img || (mlx_image_to_window(app.mlx, app.img, 0, 0) < 0))
		ft_error(1);
	mlx_loop_hook(app.mlx, frame, &app);
	mlx_loop(app.mlx);

	//matrix testing

	printf("Original test matrix\n");
	t_mat M = test_matrix_4();
	t_mat M_identity = create_identity_matrix(4);
	print_matrix(&M);
	t_tuple T = create_point(1, 2, 3);
	t_tuple T_out = multiply_matrix_and_tuple(&M, &T);
	printf("Multiplied test matrix and tuple\n");
	print_tuple(&T_out);
	printf("submatrix testing\n");
	t_mat M_sub = submatrix(&M, 1, 2, 4);
	print_matrix(&M_sub);
	t_mat M_transposed = transpose_matrix(&M, 4);
	printf("Transposed test matrix\n");
	print_matrix(&M_transposed);
	t_mat M_trans_mult = multiply_matrices(&M, &M_transposed);
	printf("Multiplied test matrix and transposed matrix\n");
	print_matrix(&M_trans_mult);
	printf("determinant of a matrix\n");
	float det = determinant(&M_identity, 4);
	print_matrix(&M_identity);
	printf("%f\n", det);
	printf("Matrixes are equal?\n");
	bool eq = matrices_are_equal(&M, &M);
	printf("%i\n", eq);
	printf("Is invertible?\n");
	bool inv = is_matrix_invertible(&M_identity);
	printf("%i\n", inv);
	printf("Cofactor matrix\n");
	t_mat M_cof = cofactor_matrix(&M);
	print_matrix(&M_cof);
	printf("Matrix inversion\n");
	t_mat M_inv = invert_matrix(&M);
	print_matrix(&M_inv);

	//end matrix testing

	code = cleanup(&app.system);
	mlx_terminate(app.mlx);
	return (code);
}
