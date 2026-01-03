/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:08:24 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/02 14:27:12 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_tuple	apply_green_tint(t_tuple *color)
{
	t_tuple	tinted;

	tinted.x = color->x * 0.7f;
	tinted.y = color->y * 1.3f;
	tinted.z = color->z * 0.7f;
	tinted.w = color->w;
	return (tinted);
}

static void	fill_pixel_block(mlx_image_t *img, int x, int y, uint32_t color)
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

static t_tuple	calculate_light_contribution(t_system *sys, t_material *mat,
		t_shader_computs *comps, int i)
{
	t_tuple	color;
	t_tuple	contrib;

	color = create_color(0, 0, 0, 1);
	comps->light_dir = calculate_light_direction(&sys->light_list[i].location,
			&comps->point);
	contrib = calculate_diffuse(mat, &sys->light_list[i], comps);
	color = add_tuple(&color, &contrib);
	contrib = calculate_specular(mat, &sys->light_list[i], comps);
	color = add_tuple(&color, &contrib);
	return (color);
}

static t_tuple	shade_hit(t_system *sys, t_material *mat,
		t_shader_computs *comps)
{
	t_tuple	color;
	t_tuple	contrib;
	int		i;
	int		light_limit;

	color = calculate_ambient(mat, &sys->amb_light);
	if (sys->render_flags & RENDER_SKIP_MULTILIGHT)
		light_limit = 1;
	else
		light_limit = sys->light_count;
	i = 0;
	while (i < light_limit)
	{
		if ((sys->render_flags & RENDER_SKIP_SHADOWS) || !is_shadowed(sys,
				&sys->light_list[i].location, &comps->over_point))
		{
			contrib = calculate_light_contribution(sys, mat, comps, i);
			color = add_tuple(&color, &contrib);
		}
		i++;
	}
	return (color);
}

t_tuple	color_at(t_system *sys, t_ray *ray)
{
	t_intersection_list	intersections;
	t_shader_computs	comps;
	t_intersection		*closest_hit;
	t_material			*mat;
	t_tuple				color;

	intersections = intersect_world(sys, ray);
	closest_hit = hit(&intersections);
	if (closest_hit == NULL)
		return (create_color(0, 0, 0, 1));
	mat = &closest_hit->object->material;
	if (mat == NULL)
		return (create_color(0, 0, 0, 1));
	comps = prepare_shading_computations(closest_hit, ray);
	color = shade_hit(sys, mat, &comps);
	color = clamp_tuple(&color, 0.0f, 1.0f);
	color.w = 1.0f;
	return (color);
}

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
