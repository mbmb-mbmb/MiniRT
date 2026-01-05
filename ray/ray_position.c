/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_position.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:08:21 by mbonsdor          #+#    #+#             */
/*   Updated: 2025/12/26 16:08:22 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_tuple	ray_position(t_ray *ray, float t)
{
	t_tuple	v_pos;
	t_tuple	v_dirmult;

	v_dirmult = multiply_tuple(&ray->direction, t);
	v_pos = add_tuple(&ray->origin, &v_dirmult);
	return (v_pos);
}
