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

# define HEIGHT 512
# define CANVAS_HEIGHT 3.0f
# define WIDTH 1024
# define EPSILON 0.00001
# define FLOAT_MAX 3.40282347e+38F
# define MAX_LIGHTS 256
# define MAX_OBJECTS 512
# define VECTOR 0.0f
# define POINT 1.0f
# define TUPLE_INCORRECT 2.0f
# define MAX_INTERSECTIONS 1024

# define MATERIAL_AMBIENT 0.1f
# define MATERIAL_DIFFUSE 0.5f
# define MATERIAL_SPECULAR 1.0f
# define MATERIAL_SHININESS 100.0f
// # define M_PI 3.14159265358979323846

typedef enum e_sys_state
{
	DRAFT_MODE = (1 << 0),
	RENDER_COMPLETE = (1 << 1),
	SHOULD_EXIT = (1 << 2),
	PARSING = (1 << 3),
	INIT = (1 << 4),
}					t_sys_state;

typedef enum e_matrix_type
{
	FOUR,
	THREE,
	TWO
}	t_matrix_type;

typedef	struct s_mat
{
	t_matrix_type	type;
	float			m[4][4];
}			t_mat;

typedef struct s_tuple
{
	float			x;
	float			y;
	float			z;
	float			w;
}					t_tuple;

typedef struct s_ray
{
	t_tuple			origin;
	t_tuple			direction;
}					t_ray;

typedef enum e_obj_state
{
	ALONE,
	IN_GROUP,
}					t_obj_state;

typedef struct s_material
{
	float			ambient;
	float			diffuse;
	float			specular;
	float			shininess;
	t_tuple			color;
}					t_material;

typedef struct s_plane
{
	t_material		material;
	t_obj_state		state;
	t_tuple			location;
	t_tuple			rotation;
	t_mat			transform_to_world;
	t_mat			inv_transform_to_obj;
	bool			is_transformed;
}					t_plane;

typedef struct s_sphere
{
	t_material		material;
	t_obj_state		state;
	t_tuple			location;
	t_tuple			rotation;
	t_mat			transform_to_world;
	t_mat			inv_transform_to_obj;
	bool			is_transformed;
	float			radius;
}					t_sphere;

typedef struct s_cylinder
{
	t_material		material;
	t_obj_state		state;
	t_tuple			location;
	t_tuple			rotation;
	t_mat			transform_to_world;
	t_mat			inv_transform_to_obj;
	bool			is_transformed;
	float			diameter;
	float			length;
	t_plane			n_cap;
	t_plane			s_cap;
}					t_cylinder;

typedef enum e_type_flag
{
	PLANE,
	SPHERE,
	CYLINDER,
	END
}					t_type_flag;

typedef struct s_object
{
	t_type_flag	type;
	union {
		t_plane		plane;
		t_sphere	sphere;
		t_cylinder	cylinder;
    };
}					t_object;

typedef struct s_intersection
{
	float			t;
	t_tuple			point;
	t_object		*object;
}					t_intersection;

typedef struct s_intersection_list
{
	t_intersection	intersections[MAX_INTERSECTIONS];
	t_intersection	*hit;
	int				count;
}					t_intersection_list;

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
	t_sphere		sphere;
	int				fov;
	float			aspect_ratio;
	t_mat			transform;
	t_mat			inverse;
}					t_camera;

typedef struct s_spot_light
{
	float			range;
	t_tuple			location;
	t_tuple			rotation;
	int				size;
	t_tuple			color;
}					t_spot_light;

typedef struct s_amb_light
{
	float			range;
	t_tuple			color;
}					t_amb_light;

typedef struct s_shader_computations
{
	t_tuple			point;
	t_tuple			eyev;
	t_tuple			normalv;
	t_tuple			reflectv;
	t_tuple			color;
	t_tuple			light_dir;
	float			over_point;
	float			ambient;
	float			diffuse;
	float			specular;
	bool			inside;
}					t_shader_computations;

typedef struct s_system
{
	t_sys_state		state;
	int				exit_code;
	t_camera		camera;
	t_object		obj_list[MAX_OBJECTS];
	int				object_count;
	t_amb_light		amb_light;
	t_spot_light	light_list[MAX_LIGHTS];
	int				light_count;
	t_world			world;
}					t_system;

typedef struct s_app
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_system		system;
}					t_app;

void				rt_parser(char *input, t_system *sys);

float				magnitude_vector(t_tuple *a);
uint32_t			pack_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
t_mat				create_identity_matrix(int dim);

#endif
