/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyniemit <jyniemit@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:22:19 by jyniemit          #+#    #+#             */
/*   Updated: 2026/01/05 14:22:19 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	intersect_plane(t_ray *ray, t_intersection_list *list)
{
	if (is_float_equal(ray->direction.y, 0.0f))
		return ;
	if (list->count < MAX_INTERSECTIONS)
		list->intersections[list->count++].t = -ray->origin.y
			/ ray->direction.y;
}
