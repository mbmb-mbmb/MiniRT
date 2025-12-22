#include "minirt.h"

t_tuple	multiply_tuple_w_tuple(t_tuple *a, t_tuple *b)
{
	t_tuple	result;

	result.x = a->x * b->x;
	result.y = a->y * b->y;
	result.z = a->z * b->z;
	result.w = 1.0f;
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
