#include "minirt.h"

static void	ft_error(int error_code)
{
	exit(error_code);
}
void	print_matrix(t_mat *M)
{
	printf("%f %f %f %f\n", M.m[0][0], M.m[0][1], M.m[0][2], M.m[0][3]);
	printf("%f %f %f %f\n", M.m[1][0], M.m[1][1], M.m[1][2], M.m[1][3]);
	printf("%f %f %f %f\n", M.m[2][0], M.m[2][1], M.m[2][2], M.m[2][3]);
	printf("%f %f %f %f\n", M.m[3][0], M.m[3][1], M.m[3][2], M.m[3][3]);
}

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

	t_mat M = create_identity_matrix(4);
	print_matrix(M);
	code = cleanup(&app.system);
	mlx_terminate(app.mlx);
	return (code);
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

t_mat create_matrix_4(float m[4][4])
{
	t_mat	matrix;

	matrix.type = FOUR;
	matrix.m[0] = *m[0];
	matrix.m[1] = *m[1];
	matrix.m[2] = *m[2];
	matrix.m[3] = *m[3];
	return (matrix);
}

t_mat	create_matrix_2(float m[2][2])
{
	t_mat	matrix;

	matrix = (t_mat){};
	matrix.type = TWO;
	matrix[0][0] = m[0][0];
	matrix[0][1] = m[0][1];
	matrix[1][0] = m[1][0];
	matrix[1][1] = m[1][1];
	return (matrix);
}

t_mat	create_matrix_3(float m[3][3])
{
	t_mat	matrix;

	matrix = (t_mat){};
	matrix.type = THREE;
	matrix[0][0] = m[0][0];
	matrix[0][1] = m[0][1];
	matrix[0][2] = m[0][2];
	matrix[1][0] = m[1][0];
	matrix[1][1] = m[1][1];
	matrix[1][2] = m[1][2];
	matrix[2][0] = m[2][0];
	matrix[2][1] = m[2][1];
	matrix[2][2] = m[2][2];
	return (matrix);
}

int	get_matrix_dim(t_mat *M, t_mat *B)
{
	if (B == NULL || (M->type == B->type))
	{
		if (M->type = THREE)
			return (3);
		if (M->type = TWO)
			return (2);
		if (M->type = FOUR)
			return (4);
	}
	ft_error(13); //TODO
	return (-1);
}

bool	matrices_are_equal(t_mat *a, t_mat *b)
{
	bool	result;
	return (result);
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
	while(i < 3)
	{
		j = 0;
		while(j < 3)
		{
			roow = row(A, i);
			cool = col(B, j);
			M.m[i][j] = dot_product_tuple(&roow, &cool);
			j++;
		}
		i++;
	}
	return (M);
}

t_tuple	multiply_matrix_and_tuple(t_mat *A, t_tuple *tup)
{
	int		i;
	int		j;
	t_tuple	T;
	t_tuple	roow;
	t_tuple	cool;

	i = 0;
	while(i < 3)
	{
		j = 0;
		while(j < 3)
		{
			roow = row(A, i);
			T[i] = dot_product_tuple(&roow, tup);
			j++;
		}
		i++;
	}
	return (T);
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
	return (M);
}

void	transpose_matrix(t_mat *M, int dim)
{
	int	i;
	int	j;
	int	temp;

	i = 0;
	while(i < dim - 1)
	{
		j = 0;
		while(j < dim -1)
		{
			temp = M[i][j];
			M[i][j] = M[j][i];
			M[j][i] = temp;
			j++;
		}
		i++;
	}
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
			out[i_out][j_out] = M[i_M][j_M];
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

t_mat	invert_matrix(t_mat *mat)
{
}

t_mat	determinant_of_matrix(t_mat *M, int dim)
{
	if (dim == 1)
		return (M[0][0]);
	if (dim == 2)
		return (M[0][0] * M[1][1] - M[0][1] * M[1][0]);
	while()
}



minor_of_matrix()
{

}

cofactor_of_matrix()
{

}
