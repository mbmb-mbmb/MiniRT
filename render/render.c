/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:08:24 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/05 15:54:58 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static void	render_pass_draft(t_system *sys, mlx_image_t *img)
{
	int		x;
	int		y;
	t_ray	ray;
	t_tuple	color;
	t_tuple	tinted;

	y = 0;
	while (y < (int)img->height)
	{
		x = 0;
		while (x < (int)img->width)
		{
			ray = ray_for_pixel(&sys->camera, (uint32_t)x, (uint32_t)y);
			color = color_at(sys, &ray);
			tinted = apply_green_tint(&color);
			fill_pixel_block(img, x, y, tuple_to_rgba(&tinted));
			x += 16;
		}
		y += 16;
	}
}

static void	render_pass_final(t_system *sys, mlx_image_t *img)
{
	int		x;
	int		y;
	t_ray	ray;
	t_tuple	color;
	int		lines_per_frame;

	lines_per_frame = 16;
	y = sys->render_line;
	while (y < (int)img->height && y < sys->render_line + lines_per_frame)
	{
		x = 0;
		while (x < (int)img->width)
		{
			ray = ray_for_pixel(&sys->camera, (uint32_t)x, (uint32_t)y);
			color = color_at(sys, &ray);
			mlx_put_pixel(img, x, y, tuple_to_rgba(&color));
			x++;
		}
		y++;
	}
	sys->render_line = y;
	if (sys->render_line >= (int)img->height)
		sys->state |= RENDER_COMPLETE;
}

void	render(t_system *sys, mlx_image_t *img)
{
	if (!(sys->state & DRAFT_RENDERED))
	{
		sys->render_flags = RENDER_SKIP_SHADOWS | RENDER_SKIP_MULTILIGHT
			| RENDER_DRAFT_BLOCKS;
		render_pass_draft(sys, img);
		sys->state |= DRAFT_RENDERED;
		sys->render_line = 0;
	}
	else if (!(sys->state & RENDER_COMPLETE))
	{
		sys->render_flags = 0;
		render_pass_final(sys, img);
	}
}
