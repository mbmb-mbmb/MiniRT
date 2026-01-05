/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:07:10 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/02 11:16:33 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_tuple	reflect(t_tuple *vec, t_tuple *normal)
{
	t_tuple	v_reflected;
	t_tuple	v_temp;
	float	dot;

	dot = dot_product_tuple(vec, normal);
	v_temp = multiply_tuple(normal, 2.0f * dot);
	v_reflected = subtract_tuple(vec, &v_temp);
	return (v_reflected);
}
