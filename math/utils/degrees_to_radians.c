/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   degrees_to_radians.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:07:41 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/05 15:55:52 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

float	degrees_to_radians(float degrees)
{
	return (degrees * M_PI / 180.0);
}
