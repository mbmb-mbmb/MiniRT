/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:08:16 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/05 15:55:06 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

t_tuple	create_color(float red, float green, float blue, float alpha)
{
	t_tuple	color;

	color.x = red;
	color.y = green;
	color.z = blue;
	color.w = alpha;
	return (color);
}
