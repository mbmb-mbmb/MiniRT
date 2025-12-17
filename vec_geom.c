#include "minirt.h"

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
	t_tuple	tmp;

	tmp.x = a->x * -1;
	tmp.y = a->y * -1;
	tmp.z = a->z * -1;
	tmp.w = a->w;
	return (tmp);
}

t_tuple	multiply_tuple(t_tuple *a, float mult)
{
	t_tuple	result;

	result = (t_tuple){};
	result.x = a->x * mult;
	result.y = a->y * mult;
	result.z = a->z * mult;
	result.w = a->w;
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
