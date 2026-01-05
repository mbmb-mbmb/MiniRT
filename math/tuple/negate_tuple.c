/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negate_tuple.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:08:54 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/05 15:55:28 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

t_tuple	negate_tuple(const t_tuple *a)
{
	t_tuple	tmp;

	tmp.x = a->x * -1;
	tmp.y = a->y * -1;
	tmp.z = a->z * -1;
	tmp.w = a->w;
	return (tmp);
}
