#include "minirt.h"

t_tuple	create_point(float x, float y, float z);
void	render(t_system *sys, mlx_image_t *img);
t_tuple	ray_position(t_ray *ray, float t);
t_tuple	lighting(t_material *material, t_amb_light *amb_light,
	t_spot_light *light, t_shader_computations *comps);

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
	render(sys, img);
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

bool	is_float_zero(float f)
{
	return (fabsf(f) < EPSILON);
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

t_tuple	multiply_tuple_w_tuple(t_tuple *a, t_tuple *b)
{
	t_tuple	result;

	result.x = a->x * b->x;
	result.y = a->y * b->y;
	result.z = a->z * b->z;
	result.w = 1.0f;
	return (result);
}

t_tuple	divide_tuple(t_tuple *a, float div)
{
	t_tuple	result;

	result = (t_tuple){};
	result.w = TUPLE_INCORRECT;
	if (is_float_zero(div))
		return (result);
	result = (t_tuple){.x = a->x / div, .y = a->y / div, .z = a->z / div,
		.w = a->w};
	return (result);
}

t_tuple	clamp_tuple(t_tuple *in, float min, float max)
{
	t_tuple	clamped;

	clamped.x = fminf(max, fmaxf(min, in->x));
	clamped.y = fminf(max, fmaxf(min, in->y));
	clamped.z = fminf(max, fmaxf(min, in->z));
	clamped.w = 1.0f;
	return (clamped);
}

float	magnitude_vector(t_tuple *a)
{
	return (sqrtf(a->x * a->x + a->y * a->y + a->z * a->z));
}

t_tuple	normalize_vector(t_tuple *a)
{
	float	mag;
	t_tuple	v_result;
	int		ak;

	v_result = (t_tuple){};
	v_result.w = TUPLE_INCORRECT;
	ak = classify_w(a);
	if (ak != VECTOR)
		return (v_result);
	mag = magnitude_vector(a);
	if (mag < EPSILON)
		return (v_result);
	v_result = (t_tuple){.x = a->x / mag, .y = a->y / mag, .z = a->z / mag,
		.w = VECTOR};
	return (v_result);
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
	t_tuple	v_result;
	int		ak;
	int		bk;

	v_result = (t_tuple){};
	v_result.w = TUPLE_INCORRECT;
	ak = classify_w(a);
	bk = classify_w(b);
	if (ak != VECTOR || bk != VECTOR)
		return (v_result);
	v_result = (t_tuple){.x = a->y * b->z - a->z * b->y, .y = a->z * b->x - a->x
		* b->z, .z = a->x * b->y - a->y * b->x, .w = VECTOR};
	return (v_result);
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
	t_tuple	row_result;
	t_tuple	col_result;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			row_result = row(A, i);
			col_result = col(B, j);
			mat.m[i][j] = dot_product_tuple_naive(&row_result, &col_result);
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
	t_tuple	row_result;

	i = 0;
	while (i < 4)
	{
		row_result = row(A, i);
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
			mat_trans.m[j][i] = mat->m[i][j];
			//mat_trans.m[i][j] = temp[i][j];
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
	float	cof;
	float	det;
	int		i;
	int		j;
	int		dim;

	dim = get_matrix_dim(mat, NULL);
	det = determinant(mat, dim);
	i = 0;
	if (is_float_zero(det))
		return (create_identity_matrix(4));
	while (i < dim)
	{
		j = 0;
		while (j < dim)
		{
			cof = cofactor_one_cell(mat, j, i, dim);
			mat_inv.m[i][j] = cof / det;
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

void	set_transform(t_object *obj, t_mat *transform)
{
	t_mat	inverse;

	if (obj->type == SPHERE)
	{
		obj->sphere.transform_to_world = *transform;
		inverse = invert_matrix(transform);
		obj->sphere.inv_transform_to_obj = inverse;
		obj->sphere.is_transformed = true;
	}
	// TODO: PLANE, CYLINDER
}

//Shading

t_tuple	normal_at(t_sphere *sphere, t_tuple *world_point)
{
	t_tuple	object_point;
	t_tuple	object_normal;
	t_tuple	world_normal;
	t_tuple	origin;
	t_mat	transposed_inverse;

	object_point = multiply_matrix_and_tuple(&sphere->inv_transform_to_obj, world_point);
	origin = create_point(0, 0, 0);
	object_normal = subtract_tuple(&object_point, &origin);
	transposed_inverse = transpose_matrix(&sphere->inv_transform_to_obj, 4);
	world_normal = multiply_matrix_and_tuple(&transposed_inverse, &object_normal);
	world_normal.w = VECTOR;
	return (normalize_vector(&world_normal));
}

t_tuple	reflect(t_tuple *vec, t_tuple *normal)
{
	t_tuple	v_reflected;
	t_tuple	v_temp;
	float	dot;

	dot = dot_product_tuple(vec, normal);
	v_temp = multiply_tuple(normal, 2.0f * dot);
	v_reflected = subtract_tuple(vec, &v_temp);
	return (v_reflected);
}

t_shader_computations	prepare_shading_computitions(t_intersection *hit, t_ray *world_ray, t_object *obj)
{
	t_shader_computations	comps;

	comps.point = ray_position(world_ray, hit->t);
	comps.eyev = negate_tuple(&world_ray->direction);
	comps.normalv = normal_at(&obj->sphere, &comps.point);
	comps.inside = false;  //TODO: Implement actual check for this.
	return (comps);
}

t_tuple	calculate_ambient(t_material *material, t_amb_light *amb_light)
{
	t_tuple	ambient;
	t_tuple	color;
	t_tuple	with_range;

	color = multiply_tuple_w_tuple(&material->color, &amb_light->color);
	ambient = multiply_tuple(&color, material->ambient);
	with_range = multiply_tuple(&ambient, amb_light->range);
	return (with_range);
}

bool	is_light_behind_surface(t_tuple *light_dir, t_tuple *normal)
{
	return (dot_product_tuple(light_dir, normal) < 0);
}

t_tuple	calculate_diffuse(t_material *material, t_spot_light *light, t_tuple *light_dir, t_tuple *normalv)
{
	t_tuple	diffuse;
	t_tuple	color;
	float	scalar;

	if (is_light_behind_surface(light_dir, normalv))
		return (create_color(0, 0, 0, 1));
	color = multiply_tuple_w_tuple(&material->color, &light->color);
	scalar = material->diffuse * light->range * dot_product_tuple(light_dir, normalv);
	diffuse = multiply_tuple(&color, scalar);
	return (diffuse);
}

bool	is_reflection_away_from_eye(t_tuple *refl, t_tuple *eye)
{
	return (dot_product_tuple(refl, eye) < 0);
}

t_tuple	calculate_specular(t_material *material, t_spot_light *light,
			t_tuple *light_dir, t_tuple *normalv, t_tuple *eyev)
{
	t_tuple	specular;
	t_tuple neg_lightv;
	t_tuple	reflectv;
	float 	factor;

	if (is_light_behind_surface(light_dir, normalv))
		return (create_color(0, 0, 0, 1));
	neg_lightv = negate_tuple(light_dir);
	reflectv = reflect(&neg_lightv, normalv);
	if (is_reflection_away_from_eye(&reflectv, eyev))
		return (create_color(0, 0, 0, 1));
	factor = powf(dot_product_tuple(&reflectv, eyev), material->shininess);
	specular = multiply_tuple(&light->color,
							material->specular * light->range * factor);
	return (specular);
}

t_tuple calc_light_direction(t_tuple *light_pos, t_tuple *point)
{
	t_tuple	direction;

	direction = subtract_tuple(light_pos, point);
	return (normalize_vector(&direction));
}

t_tuple	lighting(t_material *material, t_amb_light *amb_light,
					t_spot_light *light, t_shader_computations *comps)
{
	t_tuple	ambient;
	t_tuple	diffuse;
	t_tuple	specular;
	t_tuple	light_dirv;
	t_tuple	result;

	light_dirv = calc_light_direction(&light->location, &comps->point);
	ambient = calculate_ambient(material, amb_light);
	diffuse = calculate_diffuse(material, light, &light_dirv, &comps->normalv);
	specular = calculate_specular(material, light, &light_dirv, &comps->normalv, &comps->eyev);
	result = add_tuple(&ambient, &diffuse);
	result = add_tuple(&result, &specular);
	result = clamp_tuple(&result, 0.0f, 1.0f);

	return (result);
}
/*RAY-SPHERE */

t_tuple	ray_position(t_ray *ray, float t)
{
	t_tuple	v_pos;
	t_tuple	v_dirmult;

	v_dirmult = multiply_tuple(&ray->direction, t);
	v_pos = add_tuple(&ray->origin, &v_dirmult);
	return (v_pos);
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

t_ray	ray_to_object_space(t_ray *ray, t_object *obj)
{
	t_ray	obj_ray;

	if (obj->sphere.is_transformed)
		obj_ray = transform_ray(ray, &obj->sphere.inv_transform_to_obj);
	else
		obj_ray = *ray;
	return (obj_ray);
}

void	append_intersections(t_intersection_list *dst, t_intersection_list *src)
{
	int	i;

	i = 0;
	while (i < src->count && dst->count < MAX_INTERSECTIONS)
	{
		dst->intersections[dst->count] = src->intersections[i];
		dst->count++;
		i++;
	}
}

bool	ray_misses_sphere(float a, float discriminant)
{
	return (fabsf(a) < EPSILON || discriminant < 0.0f);
}

t_intersection_list	intersect_unit_sphere(t_sphere *sphere, t_ray *ray)
{
	t_intersection_list	intersections;
	float				discriminant;
	t_tuple				origin_to_center;
	float				a;
	float				b;
	float				c;
	(void)sphere;

	intersections = (t_intersection_list){0};
	intersections.count = 0;
	origin_to_center = ray->origin;
	origin_to_center.w = VECTOR;
	a = dot_product_tuple(&ray->direction, &ray->direction);
	b = 2 * dot_product_tuple(&ray->direction, &origin_to_center);
	c = dot_product_tuple(&origin_to_center, &origin_to_center) - 1.0;
	discriminant = b * b - 4 * a * c;
	if (ray_misses_sphere(a, discriminant))
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

t_intersection_list	intersect_world(t_system *sys, t_ray *ray)
{
	t_intersection_list	obj_intrs;
	t_intersection_list	all_intrs;
	t_ray				obj_ray;
	int					i;

	all_intrs = (t_intersection_list){0};
	all_intrs.count = 0;
	i = 0;
	while (i < sys->object_count)
	{
		obj_intrs.count = 0;
		obj_ray = ray_to_object_space(ray, &sys->obj_list[i]);
		if (sys->obj_list[i].type == SPHERE)
			obj_intrs =intersect_unit_sphere(&sys->obj_list[i].sphere, &obj_ray);
		//TODO: PLANE, CYLINDER
		append_intersections(&all_intrs, &obj_intrs);
		i++;
	}
	// TODO: sort_intersections(&all_intrs); for transparency etc.
	return (all_intrs);
}

t_intersection	*hit(t_intersection_list *intersections)
{
	t_intersection	*hit;
	float			closest_t;
	int				i;

	hit = NULL;	
	closest_t = FLOAT_MAX;
	i = 0;
	while (i < intersections->count)
	{
		if (intersections->intersections[i].t > 0.0f 
			&& intersections->intersections[i].t < closest_t)
		{
			closest_t = intersections->intersections[i].t;
			hit = &intersections->intersections[i];
		}
		i++;
	}
	return (hit);
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

t_ray	camera_ray_for_pixel(t_system *sys, uint32_t x, uint32_t y)
{
	t_ray	ray;
	t_tuple	point;

	point = window_pixel_to_canvas_point(x, y, sys);
	ray.origin = sys->camera.location;
	ray.direction = subtract_tuple(&point, &sys->camera.location);
	ray.direction = normalize_vector(&ray.direction);
	return (ray);
}

t_tuple	color_at(t_system *sys, t_ray *ray)
{
	t_intersection_list		intersections;
	t_shader_computations	comps;
	t_intersection			*closest_hit;
	t_tuple					color_at;

	intersections = intersect_world(sys, ray);
	closest_hit = hit(&intersections);
	if (closest_hit == NULL)
		return (create_color(0, 0, 0, 1));
	comps = prepare_shading_computitions(&intersections.intersections[0], ray,
				&sys->obj_list[0]);
	color_at = lighting(&sys->obj_list[0].sphere.material,
					&sys->amb_light,
					&sys->light_list[0],
					&comps);
	return (color_at);
}

uint32_t	tuple_to_rgba(t_tuple *color)
{
	return (pack_rgba((uint8_t)(color->x * 255),
						(uint8_t)(color->y * 255),
						(uint8_t)(color->z * 255),
						255));
}

void	render(t_system *sys, mlx_image_t *img)
{
	int	x;
	int	y;
	t_ray	camera_ray;
	t_tuple	color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			camera_ray = camera_ray_for_pixel(sys, x, y);
			color = color_at(sys, &camera_ray);
			mlx_put_pixel(img, x, y, tuple_to_rgba(&color));
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
	// t_intersection_list	intersect_world(t_system *sys, t_ray *ray)

	//light test
	app.system.obj_list[0].sphere.material.ambient = 0.1f;
	app.system.obj_list[0].sphere.material.diffuse = MATERIAL_DIFFUSE;
	app.system.obj_list[0].sphere.material.specular = MATERIAL_SPECULAR;
	app.system.obj_list[0].sphere.material.shininess = MATERIAL_SHININESS;

	t_mat skew_mat = skew(1.0f, 0.0f, 0, 0, 0, 0);
	set_transform(&app.system.obj_list[0], &skew_mat);
	//end test
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
