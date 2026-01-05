/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tuple_addition.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:08:49 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/05 15:55:18 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

int	validate_tuple_addition(int ak, int bk)
{
	if (ak == POINT && bk == POINT)
		return (TUPLE_INCORRECT);
	return (ak | bk);
}
