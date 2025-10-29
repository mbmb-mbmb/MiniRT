#include "minirt.h"

static int	ft_error(int error_code)
{
	exit(error_code);
}

int	main(int argc, char **av)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_data		data;	

	if(argc != 2)
		ft_error(1);

	rt_parser(av[1], &data);
	printf("A: %f (%d)\n", data.amb_light.range, data.amb_light.rgb);
	mlx = mlx_init(WIDTH, HEIGHT, "MiniRT", true);
	if (!mlx)
		ft_error(1);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error(1);
	
	mlx_put_pixel(img, WIDTH * 0.25, HEIGHT * 0.25, data.amb_light.rgb);
	mlx_put_pixel(img, WIDTH * 0.25, HEIGHT * 0.75, data.amb_light.rgb);
	mlx_put_pixel(img, WIDTH * 0.5, HEIGHT * 0.5, data.amb_light.rgb);
	mlx_put_pixel(img, WIDTH * 0.75, HEIGHT * 0.25, data.amb_light.rgb);
	mlx_put_pixel(img, WIDTH * 0.75, HEIGHT * 0.75, data.amb_light.rgb);

	//mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);

	return (0);
}
