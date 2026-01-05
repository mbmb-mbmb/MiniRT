/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sphere.c                                     :+:      :+:    :+:   */
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

void	check_sphere(char *buffer, t_system *sys)
{
	int			i;
	t_object	*obj;

	i = 0;
	while (buffer[i])
	{
		if (ft_strncmp(buffer + i, "sp", 2) == 0 && (i == 0 || buffer[i - 1]
				== '\n'))
		{
			i += 2;
			max_object_check(sys);
			obj = &sys->obj_list[sys->object_count++];
			obj->type = SPHERE;
			obj->flags = OBJ_VISIBLE | OBJ_CASTS_SHADOW;
			phong_to_material(&obj->material);
			i += parse_vector3(buffer + i, &obj->sphere.location, POINT, sys);
			i += parse_float(buffer + i, &obj->sphere.radius, POSITIVE, sys);
			i += parse_rgb_color(buffer + i, &obj->material.color, sys);
			i += skip_to_end(buffer + i, sys);
			continue ;
		}
		i++;
	}
}
