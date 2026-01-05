/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cross_product_tuple.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:09:04 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/01 12:09:47 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

t_tuple	cross_product_tuple(t_tuple *a, t_tuple *b)
{
	t_tuple	v_result;
	int		ak;
	int		bk;

	v_result = (t_tuple){};
	v_result.w = TUPLE_INCORRECT;
	ak = get_tuple_type(a);
	bk = get_tuple_type(b);
	if (ak != VECTOR || bk != VECTOR)
		return (v_result);
	v_result = (t_tuple){.x = a->y * b->z - a->z * b->y, .y = a->z * b->x - a->x
		* b->z, .z = a->x * b->y - a->y * b->x, .w = VECTOR};
	return (v_result);
}
