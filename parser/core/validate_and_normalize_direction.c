/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_and_normalize_direction.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:08:29 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/05 15:54:39 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

void	validate_and_normalize_direction(t_tuple *vec, t_system *sys)
{
	float	len;

	len = magnitude_vector(vec);
	if (len < EPSILON)
	{
		error_exit("Vector is a zero vector.\n", sys);
		return ;
	}
	if (fabsf(len - 1.0f) > 0.01f)
	{
		printf("Warning: vector not normalized (len=%.3f), normalizing...\n",
			len);
		*vec = normalize_vector(vec);
	}
}
