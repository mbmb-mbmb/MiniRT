/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonsdor <mbonsdor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:12:49 by mbonsdor          #+#    #+#             */
/*   Updated: 2026/01/05 15:01:19 by jyniemit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
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
# define SHADOW_EPSILON 0.001
# define FLOAT_MAX 3.40282347e+38F
# define MAX_LIGHTS 256
# define MAX_OBJECTS 512
# define VECTOR 0.0f
# define POINT 1.0f
# define TUPLE_INCORRECT 2.0f
# define MAX_INTERSECTIONS 1024
# define INFILE_BUFSIZE 16384

# define MATERIAL_AMBIENT 0.1f
# define MATERIAL_DIFFUSE 0.5f
# define MATERIAL_SPECULAR 1.0f
# define MATERIAL_SHININESS 50.0f

typedef enum e_sys_state
{
	DRAFT_MODE = (1 << 0),
	RENDER_COMPLETE = (1 << 1),
	SHOULD_EXIT = (1 << 2),
	PARSING = (1 << 3),
	INIT = (1 << 4),
	DRAFT_RENDERED = (1 << 5),
}					t_sys_state;

typedef enum e_render_flags
{
	RENDER_SKIP_SHADOWS = (1 << 0),
	RENDER_SKIP_MULTILIGHT = (1 << 1),
	RENDER_DRAFT_BLOCKS = (1 << 2),
}					t_render_flags;

typedef enum e_matrix_type
{
	FOUR,
	THREE,
	TWO
}	t_matrix_type;

typedef enum e_float_check
{
	ANY,
	POSITIVE,
	RATIO_0_1
}	t_float_check;

typedef struct s_mat
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
	t_tuple			location;
	t_tuple			rotation;
	t_mat			transform_to_world;
	t_mat			inv_transform_to_obj;
	bool			is_transformed;
}					t_plane;

typedef struct s_sphere
{
	t_tuple			location;
	t_mat			transform_to_world;
	t_mat			inv_transform_to_obj;
	bool			is_transformed;
	float			radius;
}					t_sphere;

typedef struct s_cylinder
{
	t_tuple			location;
	t_tuple			rotation;
	t_mat			transform_to_world;
	t_mat			inv_transform_to_obj;
	bool			is_transformed;
	float			diameter;
	float			length;
}					t_cylinder;

typedef enum e_type_flag
{
	PLANE,
	SPHERE,
	CYLINDER
}					t_type_flag;

typedef enum e_obj_flags
{
	OBJ_HAS_TRANSFORM = (1 << 0),
	OBJ_CASTS_SHADOW = (1 << 1),
	OBJ_VISIBLE = (1 << 2),
}					t_obj_flags;

typedef struct s_object
{
	t_type_flag	type;
	uint32_t	flags;
	t_material	material;
	union
	{
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

typedef struct s_canvas_dims
{
	float			half_width;
	float			half_height;
	float			pixel_size;
}	t_canvas_dims;

typedef struct s_transform_components
{
	t_mat	translation_mat;
	t_mat	rotation_mat;
	t_mat	scale_mat;
}	t_transform_components;

typedef struct s_camera
{
	t_tuple			location;
	t_tuple			rotation;
	t_tuple			world_origin;
	t_tuple			original_location;
	t_tuple			original_rotation;
	int				fov;
	float			aspect_ratio;
	t_mat			transform;
	t_mat			inverse;
	t_canvas_dims	canvas_dims;
}					t_camera;

typedef struct s_spot_light
{
	float			range;
	t_tuple			location;
	t_tuple			color;
}					t_spot_light;

typedef struct s_amb_light
{
	float			range;
	t_tuple			color;
}					t_amb_light;

typedef struct s_shader_computs
{
	t_tuple			point;
	t_tuple			over_point;
	t_tuple			eyev;
	t_tuple			normalv;
	t_tuple			light_dir;
}					t_shader_computs;

typedef struct s_system
{
	t_sys_state		state;
	uint32_t		render_flags;
	int				exit_code;
	int				parser_fd;
	mlx_t			*mlx_instance;
	t_camera		camera;
	t_object		obj_list[MAX_OBJECTS];
	int				object_count;
	t_amb_light		amb_light;
	t_spot_light	light_list[MAX_LIGHTS];
	int				light_count;
	int				render_line;
}					t_system;

typedef struct s_app
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_system		system;
}					t_app;

/* parser utilities */
int					parse_fov(char *in, int *value, t_system *sys);
int					parse_int(char *in, int *value, t_system *sys);
int					skip_spaces(const char *str);
int					skip_commas(char *buffer, t_system *sys);
int					skip_float(char *buffer);
int					skip_to_end(char *buffer, t_system *sys);
int					parse_float(char *in, float *out, t_float_check check,
						t_system *sys);
int					parse_rgb_color(char *buffer,\
					t_tuple *color, t_system *sys);
int					parse_vector3(char *buffer, t_tuple *tuple, float w,
						t_system *sys);
int					validate_rt_file_extension(char *filename);

void				check_ambient_light(char *buffer, t_system *sys);
void				check_camera(char *buffer, t_system *sys);
void				check_lights(char *buffer, t_system *sys);
void				check_sphere(char *buffer, t_system *sys);
void				check_cylinder(char *buffer, t_system *s);
void				check_plane(char *buffer, t_system *sys);

void				parser(char *input, t_system *sys);
void				validate_and_normalize_direction(t_tuple *vec,\
					t_system *sys);
void				phong_to_material(t_material *material);
t_mat				create_identity_matrix(int dim);

bool				is_float_zero(float f);
bool				is_float_equal(float a, float b);
t_tuple				create_point(float x, float y, float z);
t_tuple				create_vector(float x, float y, float z);
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
t_tuple				cross_product_tuple(t_tuple *a, t_tuple *b);
int					get_tuple_type(const t_tuple *t);
int					get_w_value_for_type(int kind);
int					validate_tuple_addition(int ak, int bk);
int					validate_tuple_subtraction(int ak, int bk);
float				degrees_to_radians(float degrees);
uint32_t			tuple_to_rgba(t_tuple *color);
t_tuple				create_color(float red, float green,
						float blue, float alpha);

/* matrix helpers */
void				set_matrix_dim(t_mat *mat, int dim);
t_mat				multiply_matrices(t_mat *ina, t_mat *inb);
t_tuple				transform_tuple_by_matrix(t_mat *mat, t_tuple *tup_in);
t_mat				transpose_matrix(t_mat *mat, int dim);
t_mat				invert_matrix(t_mat *m);

/* rays */
t_ray				ray_make(t_tuple origin, t_tuple direction);
t_tuple				ray_position(t_ray *ray, float t);
t_ray				ray_transform(t_ray *ray, t_mat *mat);
t_ray				ray_to_object_space(t_ray *ray, t_object *obj);

/* intersections */
void				intersect_sphere(t_ray *ray, t_intersection_list *list);
void				intersect_plane(t_ray *ray, t_intersection_list *list);
void				intersect_cylinder(t_ray *ray, t_intersection_list *list);
void				intersect_cylinder_caps(t_ray *ray,
						t_intersection_list *list);
void				intersect_cylinder_walls(t_ray *ray,
						t_intersection_list *list);
t_intersection_list	intersect_world(t_system *sys, t_ray *ray);
t_intersection		*find_closest_intersection(t_intersection_list *list);
bool				ray_misses_cylinder(float a, float discriminant);
bool				ray_parallel_to_y(t_ray *ray);

/* transforms */
t_mat				translation(float x, float y, float z);
t_mat				scaling(float x, float y, float z);
t_mat				rotate_x(float x);
t_mat				rotate_y(float y);
t_mat				rotate_z(float z);
t_mat				create_rotation_matrix_from_axis(t_tuple *axis);
void				set_transform(t_object *obj, t_mat *transform);
t_mat				view_transform(t_tuple *eye, t_tuple *target, t_tuple *up);

/* normals */
t_tuple				normal_at_sphere(t_sphere *sphere, t_tuple *world_point);
t_tuple				normal_at_plane(t_plane *plane);
t_tuple				normal_at_cylinder(t_cylinder *cylinder,
						t_tuple *world_point);
t_tuple				reflect(t_tuple *vec, t_tuple *normal);
t_shader_computs	prepare_shading_computations(t_intersection *hit,
						t_ray *world_ray);
t_ray				ray_for_pixel(t_camera *camera, uint32_t x, uint32_t y);

/* scene setup */
void				init_system(t_system *sys);
void				init_canvas_dimensions(t_camera *camera,
						uint32_t img_width);
void				camera_transform(t_camera *camera);
void				camera_update_transform(t_camera *camera);
void				transform_sphere(t_object *obj);
void				transform_plane(t_object *obj);
void				transform_cylinder(t_object *obj);
void				prepare_scene(t_system *sys);

/* camera controls */
void				camera_move(t_camera *camera, float dx, float dy, float dz);
void				camera_rotate_yaw(t_camera *camera, float angle);
void				camera_reset(t_camera *camera);
void				handle_camera_controls(t_app *app, t_system *system);

/* render */
void				frame(void *param);
t_tuple				color_at(t_system *sys, t_ray *ray);
void				render(t_system *sys, mlx_image_t *img);
t_tuple				shade_hit(t_system *sys, t_material *mat,
						t_shader_computs *comps);
t_tuple				apply_green_tint(t_tuple *color);
void				fill_pixel_block(mlx_image_t *img, int x, int y,
						uint32_t color);

/* lighting */
t_tuple				calculate_point_to_light_direction(t_tuple *light_pos,
						t_tuple *point);
t_tuple				calculate_ambient(t_material *material,
						t_amb_light *amb_light);
t_tuple				calculate_diffuse(t_material *material, t_spot_light *light,
						t_shader_computs *comps);
t_tuple				calculate_specular(t_material *material,
						t_spot_light *light, t_shader_computs *comps);
bool				is_shadowed(t_system *sys, t_tuple *light_pos,
						t_tuple *over_point);

/* error */
void				error_exit(char *msg, t_system *sys);
#endif
