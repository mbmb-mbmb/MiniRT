/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiply_tuple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:08:54 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/05 15:55:28 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

t_tuple	multiply_tuple(t_tuple *a, float mult)
{
	t_tuple	result;

	result = (t_tuple){};
	result.x = a->x * mult;
	result.y = a->y * mult;
	result.z = a->z * mult;
	result.w = a->w;
	return (result);
}
