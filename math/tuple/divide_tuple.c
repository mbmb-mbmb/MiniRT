/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_tuple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:08:54 by mbonsdor          #+#    #+#             */
/*   Updated: 2025/12/26 16:08:55 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

t_tuple	divide_tuple(t_tuple *a, float div)
{
	t_tuple	result;

	result = (t_tuple){};
	result.w = TUPLE_INCORRECT;
	if (is_float_zero(div))
		return (result);
	result = (t_tuple){.x = a->x / div, .y = a->y / div, .z = a->z / div,
		.w = a->w};
	return (result);
}
