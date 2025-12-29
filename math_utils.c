/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:07:41 by mbonsdor          #+#    #+#             */
/*   Updated: 2025/12/26 16:07:42 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	degrees_to_radians(float degrees)
{
	return (degrees * M_PI / 180.0);
}

float	radians_to_degrees(float radians)
{
	return (radians * 180.0 / M_PI);
}
