#include "minirt.h"

bool	is_float_zero(float f)
{
	return (fabsf(f) < EPSILON);
}

bool	is_float_equal(float a, float b)
{
	return (fabsf(a - b) < EPSILON);
}

bool	is_tuple_equal(const t_tuple *a, const t_tuple *b)
{
	return (is_float_equal(a->w, b->w)
		&& is_float_equal(a->x, b->x)
		&& is_float_equal(a->z, b->z)
		&& is_float_equal(a->y, b->y));
}
