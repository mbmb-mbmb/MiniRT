/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:07:14 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/02 11:41:53 by mbonsdor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	cleanup(t_system *sys)
{
	return (sys->exit_code);
}

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
	int		code;

	app = (t_app){};
	app.system = (t_system){};
	if (argc != 2)
		error_exit(NULL, &app.system);
	init_system(&app.system);
	app.system.state |= PARSING;
	parser(av[1], &app.system);
	prepare_scene(&app.system);
	app.system.state &= ~PARSING;
	app.mlx = mlx_init(WIDTH, HEIGHT, "MiniRT", true);
	if (!app.mlx)
		error_exit("Failed to initialize MLX\n", &app.system);
	app.img = mlx_new_image(app.mlx, WIDTH, HEIGHT);
	if (!app.img || (mlx_image_to_window(app.mlx, app.img, 0, 0) < 0))
		error_exit("Failed to create image\n", &app.system);
	mlx_loop_hook(app.mlx, frame, &app);
	mlx_resize_hook(app.mlx, resize_callback, &app);
	mlx_loop(app.mlx);
	code = cleanup(&app.system);
	mlx_terminate(app.mlx);
	return (code);
}
