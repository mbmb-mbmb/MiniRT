#include "minirt.h"

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
