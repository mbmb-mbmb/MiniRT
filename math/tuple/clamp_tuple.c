/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clamp_tuple.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:09:08 by mbonsdor          #+#    #+#             */
/*   Updated: 2025/12/26 16:09:09 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

t_tuple	clamp_tuple(t_tuple *in, float min, float max)
{
	t_tuple	clamped;

	clamped.x = fminf(max, fmaxf(min, in->x));
	clamped.y = fminf(max, fmaxf(min, in->y));
	clamped.z = fminf(max, fmaxf(min, in->z));
	clamped.w = 1.0f;
	return (clamped);
}
