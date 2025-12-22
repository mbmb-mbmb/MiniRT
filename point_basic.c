#include "minirt.h"

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
