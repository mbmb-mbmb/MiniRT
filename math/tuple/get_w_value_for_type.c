/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_w_value_for_type.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:08:49 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/05 15:55:18 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

int	get_w_value_for_type(int kind)
{
	if (kind == VECTOR)
		return (0.0f);
	if (kind == POINT)
		return (1.0f);
	return (TUPLE_INCORRECT);
}
