/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:08:21 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/05 15:54:41 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_ray	ray_transform(t_ray *ray, t_mat *mat)
{
	t_ray	ray_out;

	ray_out.origin = transform_tuple_by_matrix(mat, &ray->origin);
	ray_out.direction = transform_tuple_by_matrix(mat, &ray->direction);
	ray_out.origin.w = POINT;
	ray_out.direction.w = VECTOR;
	return (ray_out);
}
