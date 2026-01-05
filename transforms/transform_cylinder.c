#include "../minirt.h"

void	transform_cylinder(t_object *obj)
{
	t_transform_components	trs;
	t_mat					temp;
	t_mat					final;
	float					radius;

	radius = obj->cylinder.diameter / 2.0f;
	trs.translation_mat = translation(obj->cylinder.location.x,
			obj->cylinder.location.y, obj->cylinder.location.z);
	trs.rotation_mat = create_rotation_matrix_from_axis(&obj->cylinder.rotation);
	trs.scale_mat = scaling(radius, obj->cylinder.length / 2.0f, radius);
	temp = multiply_matrices(&trs.rotation_mat, &trs.scale_mat);
	final = multiply_matrices(&trs.translation_mat, &temp);
	set_transform(obj, &final);
}
