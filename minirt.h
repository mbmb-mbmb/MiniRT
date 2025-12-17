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
	t_obj_state		state;
	t_tuple			location;
	t_tuple			rotation;
	t_tuple			color;
}					t_plane;

typedef struct s_sphere
{
	t_material		material;
	t_obj_state		state;
	t_tuple			location;
	t_tuple			rotation;
	float			radius;
	t_mat			transform_to_world;
	t_mat			inv_transform_to_obj;
	bool			is_transformed;
}					t_sphere;

typedef struct s_cylinder
{
	t_obj_state		state;
	t_tuple			location;
	t_tuple			rotation;
	float			length;
	float			diameter;
	t_plane			n_cap;
	t_plane			s_cap;
	t_tuple			color;
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

uint32_t			pack_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
t_mat				create_identity_matrix(int dim);
t_mat				create_matrix_2(float m[2][2]);
t_mat				create_matrix_3(float m[3][3]);

bool				is_float_zero(float f);
bool				is_float_equal(float a, float b);
t_tuple				create_point(float x, float y, float z);
t_tuple				create_vector(float x, float y, float z);
bool				is_tuple_equal(const t_tuple *a, const t_tuple *b);
t_tuple				add_tuple(const t_tuple *a, const t_tuple *b);
t_tuple				subtract_tuple(const t_tuple *a, const t_tuple *b);
t_tuple				negate_tuple(const t_tuple *a);
t_tuple				multiply_tuple(t_tuple *a, float mult);
t_tuple				multiply_tuple_w_tuple(t_tuple *a, t_tuple *b);
t_tuple				divide_tuple(t_tuple *a, float div);
t_tuple				clamp_tuple(t_tuple *in, float min, float max);
float				magnitude_vector(t_tuple *a);
t_tuple				normalize_vector(t_tuple *a);
float				dot_product_tuple(t_tuple *a, t_tuple *b);
float				dot_product_tuple_naive(t_tuple *a, t_tuple *b);
t_tuple				cross_product_tuple(t_tuple *a, t_tuple *b);
int				classify_w(const t_tuple *t);
int				canonical_w(int kind);
int				add_kind(int ak, int bk);
int				sub_kind(int ak, int bk);
float				degrees_to_radians(float degrees);
float				radians_to_degrees(float radians);

uint32_t			tuple_to_rgba(t_tuple *color);
t_tuple				create_color(float red, float green, float blue, float alpha);

/* matrix helpers */
int				get_matrix_dim(t_mat *mat, t_mat *b);
void				set_matrix_dim(t_mat *mat, int dim);
t_tuple				row(t_mat *mat, int row);
t_tuple				col(t_mat *mat, int col);
t_mat				multiply_matrices(t_mat *ina, t_mat *inb);
t_tuple				multiply_matrix_and_tuple(t_mat *mat, t_tuple *tup_in);
t_mat				transpose_matrix(t_mat *mat, int dim);
t_mat				submatrix(t_mat *mat, int row, int col, int dim);
float				determinant(t_mat *mat, int dim);
float				cofactor_one_cell(t_mat *mat, int i, int j, int dim);
t_mat				invert_matrix(t_mat *mat);
bool				matrices_are_equal(t_mat *a, t_mat *b);

/* rays */
t_ray				ray_make(t_tuple origin, t_tuple direction);
t_tuple				ray_position(t_ray *ray, float t);
t_ray				ray_transform(t_ray *ray, t_mat *mat);
t_ray				ray_to_object_space(t_ray *ray, t_object *obj);

/* intersections */
void				append_intersections(t_intersection_list *dest,
				t_intersection_list *src);
void				tag_intersections(t_intersection_list *intersections,
				t_object *object);
t_intersection_list	intersect_sphere(t_sphere *sphere, t_ray *ray);
t_intersection_list	intersect_world(t_system *sys, t_ray *ray);
t_intersection		*hit(t_intersection_list *intersections);

/* transforms */
t_mat				translation(float x, float y, float z);
t_mat				scaling(float x, float y, float z);
t_mat				rotate_x(float x);
t_mat				rotate_y(float y);
t_mat				rotate_z(float z);
t_mat				rotation_from_tuple(t_tuple *angles);
t_mat				skew(float xy, float xz, float yx, float yz, float zx, float zy);
void				set_transform(t_object *obj, t_mat *transform);

t_mat				build_orientation_from_view(t_tuple *eye, t_tuple *target, t_tuple *up);
t_mat				view_transform(t_tuple *eye, t_tuple *target, t_tuple *up);

/* normals */
t_tuple				normal_at(t_sphere *sphere, t_tuple *world_point);

t_tuple				reflect(t_tuple *vec, t_tuple *normal);
t_shader_computations	prepare_shading_computitions(t_intersection *hit, t_ray *world_ray);
t_tuple				lighting(t_material *material, t_amb_light *amb_light,
				t_spot_light *light, t_shader_computations *comps);

t_tuple				compute_pixel_on_canvas(t_camera *camera, uint32_t x, uint32_t y);
t_ray				ray_for_pixel(t_camera *camera, uint32_t x, uint32_t y);

/* scene setup */
void				init_system(t_system *sys);
void				camera_transform(t_camera *camera);
void				setup_sphere_transform(t_object *obj);
void				prepare_scene(t_system *sys);

/* render */
t_tuple				color_at(t_system *sys, t_ray *ray);
void				render(t_system *sys, mlx_image_t *img);

#endif

