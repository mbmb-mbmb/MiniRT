#include "minirt.h"

int	classify_w(const t_tuple *t)
{
	if (is_float_equal(t->w, 0.0f))
		return (VECTOR);
	if (is_float_equal(t->w, 1.0f))
		return (POINT);
	return (TUPLE_INCORRECT);
}

int	canonical_w(int kind)
{
	if (kind == VECTOR)
		return (0.0f);
	if (kind == POINT)
		return (1.0f);
	return (TUPLE_INCORRECT);
}

int	add_kind(int ak, int bk)
{
	if (ak == POINT && bk == POINT)
		return (TUPLE_INCORRECT);
	return (ak | bk);
}

int	sub_kind(int ak, int bk)
{
	if (ak == VECTOR && bk == POINT)
		return (TUPLE_INCORRECT);
	return (ak ^ bk);
}
