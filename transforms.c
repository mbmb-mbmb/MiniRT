/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transforms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:08:34 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/02 11:43:12 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	camera_transform(t_camera *camera)
{
	t_tuple	from;
	t_tuple	to;
	t_tuple	up;
	t_tuple	camera_obj_origin;

	from = camera->location;
	to = add_tuple(&from, &camera->rotation);
	up = create_vector(0, 1, 0);
	camera->transform = view_transform(&from, &to, &up);
	camera->inverse = invert_matrix(&camera->transform);
	camera_obj_origin = (t_tuple){0.0f, 0.0f, 0.0f, POINT};
	camera->world_origin = multiply_matrix_and_tuple(&camera->inverse,
			&camera_obj_origin);
}

void	setup_sphere_transform(t_object *obj)
{
	t_transform_components	trs;
	t_mat					temp;

	trs.translation_mat = translation(obj->sphere.location.x,
			obj->sphere.location.y,
			obj->sphere.location.z);
	trs.scale_mat = scaling(obj->sphere.radius,
			obj->sphere.radius,
			obj->sphere.radius);
	temp = multiply_matrices(&trs.translation_mat, &trs.scale_mat);
	set_transform(obj, &temp);
}

void	transform_plane(t_object *obj)
{
	t_mat					temp;
	t_transform_components	trs;

	trs.translation_mat = translation(obj->plane.location.x,
			obj->plane.location.y,
			obj->plane.location.z);
	trs.rotation_mat = rotation_from_axis(&obj->plane.rotation);
	temp = multiply_matrices(&trs.translation_mat, &trs.rotation_mat);
	set_transform(obj, &temp);
}

void	transform_cylinder(t_object *obj)
{
	t_transform_components	trs;
	t_mat					temp;
	t_mat					final;
	float					radius;

	radius = obj->cylinder.diameter / 2.0f;
	trs.translation_mat = translation(obj->cylinder.location.x,
			obj->cylinder.location.y, obj->cylinder.location.z);
	trs.rotation_mat = rotation_from_axis(&obj->cylinder.rotation);
	trs.scale_mat = scaling(radius, obj->cylinder.length / 2.0f, radius);
	temp = multiply_matrices(&trs.rotation_mat, &trs.scale_mat);
	final = multiply_matrices(&trs.translation_mat, &temp);
	set_transform(obj, &final);
}