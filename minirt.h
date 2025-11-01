#ifndef MINIRT_H
# define MINIRT_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 256
# define HEIGHT 256
# define EPSILON 0.00001
# define VECTOR 0.0f
# define POINT 1.0f
# define TUPLE_INCORRECT 2.0f

typedef enum e_sys_state
{
	DRAFT_MODE = (1 << 0),
	RENDER_COMPLETE = (1 << 1),
	SHOULD_EXIT = (1 << 2),
	PARSING = (1 << 3),
	INIT = (1 << 4),
}					t_sys_state;

typedef struct s_tuple
{
	float			x;
	float			y;
	float			z;
	float			w;
}					t_tuple;

typedef enum e_obj_state
{
	ALONE,
	IN_GROUP,
}					t_obj_state;

typedef struct s_plane
{
	t_obj_state		state;
	t_tuple			location;
	t_tuple			rotation;
	uint32_t		color;
}					t_plane;

typedef struct s_ball
{
	t_obj_state		state;
	t_tuple			location;
	t_tuple			rotation;
	float			diameter;
	uint32_t		color;
}					t_ball;

typedef struct s_cylinder
{
	t_obj_state		state;
	t_tuple			location;
	t_tuple			rotation;
	float			length;
	float			diameter;
	t_plane			n_cap;
	t_plane			s_cap;
	uint32_t		color;
}					t_cylinder;

typedef enum e_type_flag
{
	PLANE,
	BALL,
	CYLINDER,
	END
}					t_type_flag;

typedef union u_object
{
	t_type_flag		type;
	t_plane			plane;
	t_ball			ball;
	t_cylinder		cylinder;
}					t_object;

typedef struct s_world
{
	t_plane			heaven;
	t_plane			ground;
	t_plane			north;
	t_plane			west;
	t_plane			east;
	t_plane			south;
}					t_world;

typedef struct s_camera
{
	t_tuple			location;
	t_tuple			rotation;
	t_ball			ball;
	int				fov;
}					t_camera;

typedef struct s_spot_light
{
	double			range;
	t_tuple			location;
	t_tuple			rotation;
	int				size;
	uint32_t		color;
}					t_spot_light;

typedef struct s_amb_light
{
	double			range;
	uint32_t		rgb;
}					t_amb_light;

typedef struct s_system
{
	t_sys_state		state;
	int				exit_code;

	t_camera		*camera;
	t_object		**obj_list;
	t_amb_light		amb_light;
	t_spot_light	**light_list;
	t_world			world;
}					t_system;

typedef struct s_app
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_system		system;
}					t_app;

void				rt_parser(char *input, t_system *sys);

#endif
