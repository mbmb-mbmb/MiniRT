#include "minirt.h"

t_tuple	create_point(float x, float y, float z);
void	project_sphere(t_system *sys, mlx_image_t *img);

static void	ft_error(int error_code)
{
	exit(error_code);
}

/* DEBUGGING FUNCTIONS */
void	print_matrix(t_mat *mat)
{
	printf("%f %f %f %f\n", mat->m[0][0], mat->m[0][1], mat->m[0][2], mat->m[0][3]);
	printf("%f %f %f %f\n", mat->m[1][0], mat->m[1][1], mat->m[1][2], mat->m[1][3]);
	printf("%f %f %f %f\n", mat->m[2][0], mat->m[2][1], mat->m[2][2], mat->m[2][3]);
	printf("%f %f %f %f\n", mat->m[3][0], mat->m[3][1], mat->m[3][2], mat->m[3][3]);
}

t_mat	test_matrix_4(void)
{
	t_mat	mat;

	mat = (t_mat){};
	mat.type = FOUR;
	mat.m[0][0] = 1;
	mat.m[0][1] = 2;
	mat.m[0][2] = 3;
	mat.m[0][3] = 4;

	mat.m[1][0] = 0;
	mat.m[1][1] = 1;
	mat.m[1][2] = 2;
	mat.m[1][3] = 3;

	mat.m[2][0] = 1;
	mat.m[2][1] = 0;
	mat.m[2][2] = 1;
	mat.m[2][3] = 2;

	mat.m[3][0] = 2;
	mat.m[3][1] = 1;
	mat.m[3][2] = 0;
	mat.m[3][3] = 1;
	return (mat);
}

void	print_tuple(t_tuple *tup)
{
	printf("tup: %f, %f, %f, %f\n", tup->x, tup->y, tup->z, tup->w);
}

/* SYSTEM FUNCTIONS */

static void	init_system(t_system *sys)
{
	*sys = (t_system){0};
	sys->state = DRAFT_MODE;
	sys->exit_code = 0;
	sys->camera.aspect_ratio = (float)WIDTH / (float)HEIGHT;
}

static void	draft_transformations(t_system *sys)
{
	(void)sys;
}

static void	render_scene(t_system *sys, mlx_image_t *img)
{
	project_sphere(sys, img);
	sys->state |= RENDER_COMPLETE;
}

static int	cleanup(t_system *sys)
{
	return (sys->exit_code);
}

void    resize_callback(int32_t width, int32_t height, void *param)
{
    (void)width;
    (void)height;
    (void)param;
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

/*MATHS*/

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

t_tuple	create_color(float red, float green, float blue, float alpha)
{
	t_tuple	result;

	result = (t_tuple){.x = red, .y = green, .z = blue, .w = alpha};
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

int	get_matrix_dim(t_mat *mat, t_mat *B)
{
	if (B == NULL || (mat->type == B->type))
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

bool	matrices_are_equal(t_mat *A, t_mat *B)
{
	int	i;
	int	j;
	int	dim;

	dim = get_matrix_dim(A, B);
	if (dim == -1)
		return (false);
	i = 0;
	while (i < dim)
	{
		j = 0;
		while (j < dim)
		{
			if (A->m[i][j] != B->m[i][j])
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

t_tuple	row(t_mat *mat, int row)
{
	t_tuple	mat_row;

	mat_row.x = mat->m[row][0];
	mat_row.y = mat->m[row][1];
	mat_row.z = mat->m[row][2];
	mat_row.w = mat->m[row][3];
	return (mat_row);
}

t_tuple	col(t_mat *mat, int col)
{
	t_tuple	mat_col;

	mat_col.x = mat->m[0][col];
	mat_col.y = mat->m[1][col];
	mat_col.z = mat->m[2][col];
	mat_col.w = mat->m[3][col];
	return (mat_col);
}

t_mat	multiply_matrices(t_mat *A, t_mat *B)
{
	t_mat	mat;
	int		i;
	int		j;
	t_tuple	roow;
	t_tuple	cool;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			roow = row(A, i);
			cool = col(B, j);
			mat.m[i][j] = dot_product_tuple_naive(&roow, &cool);
			j++;
		}
		i++;
	}
	return (mat);
}

t_tuple	multiply_matrix_and_tuple(t_mat *A, t_tuple *tup_in)
{
	int		i;
	t_tuple	tup_out;
	t_tuple	roow;

	i = 0;
	while (i < 4)
	{
		roow = row(A, i);
		if (i == 0)
			tup_out.x = dot_product_tuple_naive(&roow, tup_in);
		else if (i == 1)
			tup_out.y = dot_product_tuple_naive(&roow, tup_in);
		else if (i == 2)
			tup_out.z = dot_product_tuple_naive(&roow, tup_in);
		else if (i == 3)
			tup_out.w = dot_product_tuple_naive(&roow, tup_in);
		i++;
	}
	return (tup_out);
}

t_mat	transpose_matrix(t_mat *mat, int dim)
{
	int		i;
	int		j;
	int		temp[dim][dim];
	t_mat	mat_trans;

	mat_trans.type = mat->type;
	i = 0;
	while (i < dim)
	{
		j = 0;
		while (j < dim)
		{
			temp[i][j] = mat->m[i][j];
			mat_trans.m[i][j] = mat->m[j][i];
			mat_trans.m[j][i] = temp[i][j];
			j++;
		}
		i++;
	}
	return (mat_trans);
}

t_mat	submatrix(t_mat *mat, int row, int col, int dim)
{
	int		i_mat;
	int		j_mat;
	int		i_out;
	int		j_out;
	float	out[dim - 1][dim - 1];

	i_out = 0;
	i_mat = 0;
	while (i_mat < dim)
	{
		if (i_mat == row)
		{
			i_mat++;
			continue ;
		}
		j_out = 0;
		j_mat = 0;
		while (j_mat < dim)
		{
			if (j_mat == col)
			{
				j_mat++;
				continue ;
			}
			out[i_out][j_out] = mat->m[i_mat][j_mat];
			j_mat++;
			j_out++;
		}
		i_mat++;
		i_out++;
	}
	if (dim == 4)
		return (create_matrix_3(out));
	else
		return (create_matrix_2(out));
}

float	determinant(t_mat *mat, int dim)
{
	t_mat	mat_sub;
	int		col;
	int		sign;
	float	det;
	float	det_temp;

	col = 0;
	det = 0.0f;
	sign = 0;
	if (dim == 1)
		return (mat->m[0][0]);
	if (dim == 2)
		return (mat->m[0][0] * mat->m[1][1] - mat->m[0][1] * mat->m[1][0]);
	while (col < dim)
	{
		mat_sub = submatrix(mat, 0, col, dim);
		if ((0 + col) % 2 == 0)
			sign = 1;
		else
			sign = -1;
		det_temp = determinant(&mat_sub, dim - 1);
		det += sign * mat->m[0][col] * det_temp;
		col++;
	}
	return (det);
}

float	cofactor_one_cell(t_mat *mat, int i, int j, int dim)
{
	t_mat	mat_sub;
	int		sign;
	float	c;

	mat_sub = submatrix(mat, i, j, dim);
	c = determinant(&mat_sub, dim - 1);
	if ((i + j) % 2 == 0)
		sign = 1;
	else
		sign = -1;
	return (c * sign);
}

t_mat	cofactor_matrix(t_mat *mat)
{
	t_mat	mat_out;
	int		i;
	int		j;
	int		dim;

	i = 0;
	dim = get_matrix_dim(mat, NULL);
	while (i < dim)
	{
		j = 0;
		while (j < dim)
		{
			mat_out.m[i][j] = cofactor_one_cell(mat, i, j, dim);
			j++;
		}
		i++;
	}
	return (mat_out);
}

bool	is_matrix_invertible(t_mat *mat)
{
	if (determinant(mat, get_matrix_dim(mat, NULL)) == 0)
		return (false);
	return (true);
}

t_mat	invert_matrix(t_mat *mat)
{
	t_mat	mat_inv;
	float	c;
	float	d;
	int		i;
	int		j;
	int		dim;

	dim = get_matrix_dim(mat, NULL);
	d = determinant(mat, dim);
	i = 0;
	if (d == 0)
		return (create_identity_matrix(4));
	while (i < dim)
	{
		j = 0;
		while (j < dim)
		{
			c = cofactor_one_cell(mat, j, i, dim);
			mat_inv.m[i][j] = c / d;
			j++;
		}
		i++;
	}
	return (mat_inv);
}

/*TRANSFORMATIONS*/

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

/*RAY-SPHERE INTERSECTION*/

t_tuple	ray_position(t_ray *ray, float t)
{
	t_tuple	pos;
	t_tuple	dirmult;

	dirmult = multiply_tuple(&ray->direction, t);
	pos = add_tuple(&ray->origin, &dirmult);
	return (pos);
}

t_ray	transform_ray(t_ray *ray, t_mat *mat)
{
	t_ray	ray_out;

	ray_out.origin = multiply_matrix_and_tuple(mat, &ray->origin);
	ray_out.direction = multiply_matrix_and_tuple(mat, &ray->direction);
	ray_out.origin.w = POINT;
	ray_out.direction.w = VECTOR;
	return (ray_out);
}

t_intersection_list	intersect_sphere(t_sphere *sphere, t_ray *ray)
{
	t_intersection_list	intersections;
	float				discriminant;
	t_tuple				oc;
	float				a;
	float				b;
	float				c;

	intersections = (t_intersection_list){0};
	intersections.count = 0;
	oc = subtract_tuple(&ray->origin, &sphere->location);
	a = dot_product_tuple(&ray->direction, &ray->direction);
	b = 2 * dot_product_tuple(&ray->direction, &oc);
	c = dot_product_tuple(&oc, &oc) - (sphere->radius * sphere->radius);
	discriminant = b * b - 4 * a * c;
	if (fabsf(a) < EPSILON || discriminant < 0)
		return (intersections);
	intersections.intersections[0].t = (-b - sqrtf(discriminant)) / (2 * a);
	intersections.intersections[0].point = ray_position(ray, intersections.intersections[0].t);
	intersections.intersections[0].type = SPHERE;
	intersections.intersections[1].t = (-b + sqrtf(discriminant)) / (2 * a);
	intersections.intersections[1].point = ray_position(ray, intersections.intersections[1].t);
	intersections.intersections[1].type = SPHERE;
	intersections.count = 2;
	return (intersections);
}

/*OBJ PROJECTON*/

t_tuple	window_pixel_to_canvas_point(uint32_t x, uint32_t y, t_system *sys)
{
	t_tuple	canvas_coord;
	float	canvas_width;
	
	canvas_coord = (t_tuple){0};
	canvas_width = CANVAS_HEIGHT * sys->camera.aspect_ratio;
	canvas_coord.x = ((float)x - WIDTH / 2.0f) * canvas_width / WIDTH;
	canvas_coord.y = ((HEIGHT / 2.0f - (float)y) * CANVAS_HEIGHT / HEIGHT);
	canvas_coord.z = 1.0f;
	canvas_coord.w = POINT;
	return (canvas_coord);
}

void	project_sphere(t_system *sys, mlx_image_t *img)
{
	t_ray				ray;
	t_intersection_list	intersections;
	t_tuple				canvas_point;
	t_tuple				ray_dir;
	uint32_t			x;
	uint32_t			y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			canvas_point = window_pixel_to_canvas_point(x, y, sys);
			ray_dir = subtract_tuple(&canvas_point, &sys->camera.location);
			ray_dir = normalize_tuple(&ray_dir);
			ray = (t_ray){.origin = sys->camera.location, .direction = ray_dir};
			intersections = intersect_sphere(&sys->obj_list[0].sphere, &ray);
			if (intersections.count > 0 && intersections.intersections[0].t > 0)
				mlx_put_pixel(img, x, y, sys->obj_list[0].sphere.color);
			else
				mlx_put_pixel(img, x, y, sys->amb_light.rgb);
			x++;
		}
		y++;
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
	mlx_resize_hook(app.mlx, resize_callback, &app);
	mlx_loop(app.mlx);
	code = cleanup(&app.system);
	mlx_terminate(app.mlx);
	return (code);
}
