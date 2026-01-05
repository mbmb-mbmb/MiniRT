/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_ambient.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:07:04 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/02 11:18:44 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_tuple	calculate_ambient(t_material *material, t_amb_light *amb_light)
{
	t_tuple	ambient;
	t_tuple	color;
	t_tuple	final_ambient;

	color = multiply_tuple_w_tuple(&material->color, &amb_light->color);
	ambient = multiply_tuple(&color, material->ambient);
	final_ambient = multiply_tuple(&ambient, amb_light->range);
	return (final_ambient);
}
