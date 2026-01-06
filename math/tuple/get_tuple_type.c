/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tuple_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:08:49 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/05 15:55:18 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

int	get_tuple_type(const t_tuple *t)
{
	if (is_float_equal(t->w, 0.0f))
		return (VECTOR);
	if (is_float_equal(t->w, 1.0f))
		return (POINT);
	return (TUPLE_INCORRECT);
}
