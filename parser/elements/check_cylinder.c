/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyniemit <jyniemit@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:54:21 by jyniemit          #+#    #+#             */
/*   Updated: 2026/01/05 15:54:21 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

static void	max_object_check(t_system *sys)
{
	if (sys->object_count >= MAX_OBJECTS)
		error_exit("Too many objects.\n", sys);
}

static void	parse_cylinder(char *buffer, t_object *obj, t_system *s, int i)
{
	i += parse_vector3(buffer + i, &obj->cylinder.location, POINT, s);
	i += parse_vector3(buffer + i, &obj->cylinder.rotation, VECTOR, s);
	validate_and_normalize_direction(&obj->cylinder.rotation, s);
	i += parse_float(buffer + i, &obj->cylinder.diameter, POSITIVE, s);
	i += parse_float(buffer + i, &obj->cylinder.length, POSITIVE, s);
	i += parse_rgb_color(buffer + i, &obj->material.color, s);
	i += skip_to_end(buffer + i, s);
}

void	check_cylinder(char *buffer, t_system *s)
{
	int			i;
	t_object	*obj;

	i = 0;
	while (buffer[i])
	{
		if (ft_strncmp(buffer + i, "cy", 2) == 0 && (i == 0 || buffer[i - 1]
				== '\n'))
		{
			i += 2;
			max_object_check(s);
			obj = &s->obj_list[s->object_count++];
			obj->type = CYLINDER;
			obj->flags = OBJ_VISIBLE | OBJ_CASTS_SHADOW;
			phong_to_material(&obj->material);
			parse_cylinder(buffer, obj, s, i);
			continue ;
		}
		i++;
	}
}
