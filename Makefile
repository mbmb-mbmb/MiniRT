NAME	= miniRT
LIBMLX	= MLX42
LIBFT	= libft

LIBS	= $(LIBMLX)/build/libmlx42.a $(LIBFT)/libft.a -ldl -lglfw -pthread -lm

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -O2 -ffast-math
HEADERS	= -I . -I $(LIBMLX)/include -I $(LIBFT)
# Math - Utils (3 files)
MATH_UTILS_SRC = math/utils/degrees_to_radians.c math/utils/is_float_zero.c \
                 math/utils/is_float_equal.c

# Math - Tuple (19 files)
MATH_TUPLE_SRC = math/tuple/create_point.c math/tuple/create_vector.c \
                 math/tuple/create_color.c math/tuple/tuple_to_rgba.c \
                 math/tuple/get_tuple_type.c math/tuple/get_w_value_for_type.c \
                 math/tuple/validate_tuple_addition.c \
                 math/tuple/validate_tuple_subtraction.c \
                 math/tuple/add_tuple.c math/tuple/subtract_tuple.c \
                 math/tuple/negate_tuple.c math/tuple/multiply_tuple.c \
                 math/tuple/divide_tuple.c math/tuple/multiply_tuple_w_tuple.c \
                 math/tuple/clamp_tuple.c math/tuple/magnitude_vector.c \
                 math/tuple/normalize_vector.c math/tuple/dot_product_tuple.c \
                 math/tuple/cross_product_tuple.c

# Math - Matrix (6 files)
MATH_MATRIX_SRC = math/matrix/create_identity_matrix.c \
                  math/matrix/multiply_matrices.c \
                  math/matrix/transform_tuple_by_matrix.c \
                  math/matrix/transpose_matrix.c \
                  math/matrix/set_matrix_dim.c \
                  math/matrix/invert_matrix.c

# Ray (4 files)
RAY_SRC = ray/ray_make.c ray/ray_position.c ray/ray_transform.c \
          ray/ray_to_object_space.c

# Normals (3 files)
NORMALS_SRC = normals/normal_at_sphere.c normals/normal_at_plane.c \
              normals/normal_at_cylinder.c

# Transforms (10 files)
TRANSFORMS_SRC = transforms/translation.c transforms/scaling.c \
                 transforms/rotate_x.c transforms/rotate_y.c transforms/rotate_z.c \
                 transforms/create_rotation_matrix_from_axis.c \
                 transforms/set_transform.c transforms/setup_sphere_transform.c \
                 transforms/transform_plane.c transforms/transform_cylinder.c

# Camera (4 files)
CAMERA_SRC = camera/camera_transform.c camera/camera_update_transform.c \
             camera/view_transform.c camera/ray_for_pixel.c

# Camera Controls (4 files)
CAMERA_CONTROLS_SRC = camera_controls/camera_move.c \
                      camera_controls/camera_rotate_yaw.c \
                      camera_controls/camera_reset.c \
                      camera_controls/handle_camera_controls.c

# Intersections (7 files)
INTERSECTIONS_SRC = intersections/intersect_sphere.c intersections/intersect_plane.c \
                    intersections/intersect_world.c \
                    intersections/find_closest_intersection.c \
                    intersections/intersect_cylinder.c \
                    intersections/intersect_cylinder_walls.c \
                    intersections/intersect_cylinder_caps.c

# Lighting (7 files)
LIGHTING_SRC = lighting/reflect.c lighting/is_shadowed.c \
               lighting/prepare_shading_computations.c \
               lighting/calculate_ambient.c lighting/calculate_diffuse.c \
               lighting/calculate_specular.c \
               lighting/calculate_point_to_light_direction.c

# Render (5 files)
RENDER_SRC = render/shade_hit.c render/color_at.c render/render.c \
             render/apply_green_tint.c render/fill_pixel_block.c

# Old files (keep for now, will remove after testing)
OLD_SRC = parser.c parser_utils.c parser_helpers.c parser_elements.c parser_objects.c \
          system_init.c error.c app_loop.c

SRC = main.c $(MATH_UTILS_SRC) $(MATH_TUPLE_SRC) $(MATH_MATRIX_SRC) \
      $(RAY_SRC) $(NORMALS_SRC) $(TRANSFORMS_SRC) $(CAMERA_SRC) \
      $(CAMERA_CONTROLS_SRC) $(INTERSECTIONS_SRC) $(LIGHTING_SRC) \
      $(RENDER_SRC) $(OLD_SRC)
OBJS	= $(SRC:.c=.o)

all: libft libmlx $(NAME)

libft:
	$(MAKE) -C $(LIBFT)

libmlx:
	@if [ ! -d "$(LIBMLX)" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX); \
	fi
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT) clean
	rm -rf $(LIBMLX)/build

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT) fclean
	rm -rf $(LIBMLX)

re: fclean all

.PHONY: all clean fclean re libmlx libft
