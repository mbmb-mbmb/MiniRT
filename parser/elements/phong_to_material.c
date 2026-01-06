/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_to_material.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyniemit <jyniemit@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:54:20 by jyniemit          #+#    #+#             */
/*   Updated: 2026/01/05 15:54:20 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

void	phong_to_material(t_material *material)
{
	material->ambient = MATERIAL_AMBIENT;
	material->diffuse = MATERIAL_DIFFUSE;
	material->specular = MATERIAL_SPECULAR;
	material->shininess = MATERIAL_SHININESS;
}
