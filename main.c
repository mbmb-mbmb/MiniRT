#include "minirt.h"

static int	ft_error(int error_code)
{
	exit(error_code);
}

int	main(int argc, char **av)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_system	system;

	system = (t_system){};
	if(argc != 2)
		ft_error(1);

	rt_parser(av[1], &system);
	printf("A: %f (%d)\n", system.amb_light.range, system.amb_light.rgb);
	mlx = mlx_init(WIDTH, HEIGHT, "MiniRT", true);
	if (!mlx)
		ft_error(1);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error(1);

	mlx_put_pixel(img, WIDTH * 0.25, HEIGHT * 0.25, system.amb_light.rgb);
	mlx_put_pixel(img, WIDTH * 0.25, HEIGHT * 0.75, system.amb_light.rgb);
	mlx_put_pixel(img, WIDTH * 0.5, HEIGHT * 0.5, system.amb_light.rgb);
	mlx_put_pixel(img, WIDTH * 0.75, HEIGHT * 0.25, system.amb_light.rgb);
	mlx_put_pixel(img, WIDTH * 0.75, HEIGHT * 0.75, system.amb_light.rgb);

	//mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);

	return (0);
}

// t_system	system;
// system = (t_system){};

// init_system(&system);
// if(!(state & SHOULD_EXIT))
// {
// 	if(state & DRAFT_MODE)
// 		draft_transformations(&system);
// 	if(!(state & RENDER_COMPLETE))
// 		render(&system);
// }
// return(cleanup(&system);
