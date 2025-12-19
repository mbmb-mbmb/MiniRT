#include "minirt.h"

static void ft_error(int error_code)
{
	exit(error_code);
}

/* DEBUGGING FUNCTIONS */

void	print_matrix(t_mat *mat)
{
	printf("%f %f %f %f\n", mat->m[0][0], mat->m[0][1], mat->m[0][2], mat->m[0][3]);
	printf("%f %f %f %f\n", mat->m[1][0], mat->m[1][1], mat->m[1][2], mat->m[1][3]);
	printf("%f %f %f %f\n", mat->m[2][0], mat->m[2][1], mat->m[2][2], mat->m[2][3]);
	printf("%f %f %f %f\n", mat->m[3][0], mat->m[3][1], mat->m[3][2], mat->m[3][3]);
}

void	print_tuple(t_tuple *tup)
{
	printf("tup: %f, %f, %f, %f\n", tup->x, tup->y, tup->z, tup->w);
}

/* SYSTEM FUNCTIONS */

static void	draft_transformations(t_system *sys)
{
	(void)sys;
}

static void	render_scene(t_system *sys, mlx_image_t *img)
{
	render(sys, img);
	sys->state |= RENDER_COMPLETE;
}

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
	sys->state &= ~RENDER_COMPLETE;
}

static void	frame(void *param)
{
	t_app		*app;
	t_system	*system;

	app = (t_app *)param;
	system = &app->system;
	if (mlx_is_key_down(app->mlx, MLX_KEY_ESCAPE))
		system->state |= SHOULD_EXIT;
	if (!(system->state & SHOULD_EXIT))
	{
		if (system->state & DRAFT_MODE)
			draft_transformations(system);
		if (!(system->state & RENDER_COMPLETE))
			render_scene(system, app->img);
	}
	else
		mlx_close_window(app->mlx);
}

int	main(int argc, char **av)
{
	t_app	app;
	int		code;

	app = (t_app){};
	app.system = (t_system){};
	if (argc != 2)
		ft_error(1);
	init_system(&app.system);
	rt_parser(av[1], &app.system);
	prepare_scene(&app.system);

	app.mlx = mlx_init(WIDTH, HEIGHT, "MiniRT", true);
	if (!app.mlx)
		ft_error(1);
	app.img = mlx_new_image(app.mlx, WIDTH, HEIGHT);
	if (!app.img || (mlx_image_to_window(app.mlx, app.img, 0, 0) < 0))
		ft_error(1);
	mlx_loop_hook(app.mlx, frame, &app);
	mlx_resize_hook(app.mlx, resize_callback, &app);
	mlx_loop(app.mlx);
	code = cleanup(&app.system);
	mlx_terminate(app.mlx);
	return (code);
}


/*
TODO: 
* multiple lights, should be pretty similar to looping trough the object list. Dunno.
* floor
	implement the floor plane
*/
