/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_tuple.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:08:54 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/05 15:55:28 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

t_tuple	add_tuple(const t_tuple *a, const t_tuple *b)
{
	t_tuple	result;
	int		ak;
	int		bk;
	int		rk;

	ak = get_tuple_type(a);
	bk = get_tuple_type(b);
	rk = validate_tuple_addition(ak, bk);
	result = (t_tuple){};
	result.x = a->x + b->x;
	result.y = a->y + b->y;
	result.z = a->z + b->z;
	result.w = get_w_value_for_type(rk);
	return (result);
}
