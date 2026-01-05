/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_green_tint.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyniemit <jyniemit@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 16:07:53 by jyniemit          #+#    #+#             */
/*   Updated: 2026/01/04 16:07:55 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_tuple	apply_green_tint(t_tuple *color)
{
	t_tuple	tinted;

	tinted.x = color->x * 0.7f;
	tinted.y = color->y * 1.3f;
	tinted.z = color->z * 0.7f;
	tinted.w = color->w;
	return (tinted);
}
