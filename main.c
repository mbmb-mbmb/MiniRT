/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:07:14 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/08 14:49:32 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	resize_callback(int32_t width, int32_t height, void *param)
{
	t_app		*app;
	t_system	*sys;

	app = (t_app *)param;
	sys = &app->system;
	mlx_delete_image(app->mlx, app->img);
	app->img = mlx_new_image(app->mlx, width, height);
	if (!app->img)
		return ;
	if (mlx_image_to_window(app->mlx, app->img, 0, 0) < 0)
		return ;
	sys->camera.aspect_ratio = (float)width / (float)height;
	init_canvas_dimensions(&sys->camera, width);
	sys->state &= ~RENDER_COMPLETE;
	sys->state &= ~DRAFT_RENDERED;
	sys->render_line = 0;
}

int	main(int argc, char **av)
{
	t_app	app;

	app = (t_app){};
	app.system = (t_system){};
	if (argc != 2)
		error_exit(NULL, &app.system);
	init_system(&app.system);
	parser(av[1], &app.system);
	prepare_scene(&app.system);
	app.mlx = mlx_init(WIDTH, HEIGHT, "MiniRT", true);
	if (!app.mlx)
		error_exit("Failed to initialize MLX\n", &app.system);
	app.system.mlx_instance = app.mlx;
	app.img = mlx_new_image(app.mlx, WIDTH, HEIGHT);
	if (!app.img || (mlx_image_to_window(app.mlx, app.img, 0, 0) < 0))
		error_exit("Failed to create image\n", &app.system);
	mlx_loop_hook(app.mlx, frame, &app);
	mlx_resize_hook(app.mlx, resize_callback, &app);
	mlx_loop(app.mlx);
	app.system.mlx_instance = NULL;
	mlx_terminate(app.mlx);
	return (app.system.exit_code);
}
