/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_closest_intersection.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:06:50 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/02 11:14:53 by mbonsdor         ###   ########.fr       */
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
