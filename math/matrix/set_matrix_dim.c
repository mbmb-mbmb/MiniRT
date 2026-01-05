/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_matrix_dim.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:07:35 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/05 15:03:31 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

void	set_matrix_dim(t_mat *mat, int dim)
{
	if (dim == 3)
		mat->type = THREE;
	else if (dim == 2)
		mat->type = TWO;
	else if (dim == 4)
		mat->type = FOUR;
	else
		mat->type = -1;
}
