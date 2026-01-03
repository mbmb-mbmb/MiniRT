/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:08:16 by mbonsdor          #+#    #+#             */
/*   Updated: 2025/12/26 16:08:17 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	create_point(float x, float y, float z)
{
	t_tuple	point;

	point.w = POINT;
	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

t_tuple	create_vector(float x, float y, float z)
{
	t_tuple	vector;

	vector.w = VECTOR;
	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}

static uint32_t	pack_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (((uint32_t)r << 24) | ((uint32_t)g << 16)
		| ((uint32_t)b << 8) | ((uint32_t)a));
}

uint32_t	tuple_to_rgba(t_tuple *color)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	r = (uint8_t)(color->x * 255.0f);
	g = (uint8_t)(color->y * 255.0f);
	b = (uint8_t)(color->z * 255.0f);
	a = (uint8_t)(color->w * 255.0f);
	return (pack_rgba(r, g, b, a));
}

t_tuple	create_color(float red, float green, float blue, float alpha)
{
	t_tuple	color;

	color.x = red;
	color.y = green;
	color.z = blue;
	color.w = alpha;
	return (color);
}
