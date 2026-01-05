/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_pixel_block.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyniemit <jyniemit@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 16:07:53 by jyniemit          #+#    #+#             */
/*   Updated: 2026/01/04 16:07:55 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	fill_pixel_block(mlx_image_t *img, int x, int y, uint32_t color)
{
	int	dx;
	int	dy;

	dy = 0;
	while (dy < 16 && (y + dy) < (int)img->height)
	{
		dx = 0;
		while (dx < 16 && (x + dx) < (int)img->width)
		{
			mlx_put_pixel(img, x + dx, y + dy, color);
			dx++;
		}
		dy++;
	}
}
