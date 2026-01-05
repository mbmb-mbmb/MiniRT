/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_make.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:08:21 by mbonsdor          #+#    #+#             */
/*   Updated: 2025/12/26 16:08:22 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_ray	ray_make(t_tuple origin, t_tuple direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}
