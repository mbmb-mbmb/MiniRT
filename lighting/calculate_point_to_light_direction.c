/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_point_to_light_direction.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:07:04 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/02 11:18:44 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_tuple	calculate_point_to_light_direction(t_tuple *light_pos, t_tuple *point)
{
	t_tuple	direction;

	direction = subtract_tuple(light_pos, point);
	return (normalize_vector(&direction));
}
