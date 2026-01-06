/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_closest_intersection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyniemit <jyniemit@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:22:16 by jyniemit          #+#    #+#             */
/*   Updated: 2026/01/05 14:22:16 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_intersection	*find_closest_intersection(t_intersection_list *list)
{
	t_intersection	*hit;
	float			closest_t;
	int				i;

	hit = NULL;
	closest_t = FLOAT_MAX;
	i = 0;
	while (i < list->count)
	{
		if (list->intersections[i].t > 0.0f
			&& list->intersections[i].t < closest_t)
		{
			closest_t = list->intersections[i].t;
			hit = &list->intersections[i];
		}
		i++;
	}
	return (hit);
}
