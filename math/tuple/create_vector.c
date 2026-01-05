/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_vector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:08:16 by mbonsdor          #+#    #+#             */
/*   Updated: 2025/12/26 16:08:17 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

t_tuple	create_vector(float x, float y, float z)
{
	t_tuple	vector;

	vector.w = VECTOR;
	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}
