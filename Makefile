NAME	= miniRT
LIBMLX	= MLX42
LIBFT	= libft

LIBS	= $(LIBMLX)/build/libmlx42.a $(LIBFT)/libft.a -ldl -lglfw -pthread -lm

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -O2 -ffast-math
HEADERS	= -I . -I $(LIBMLX)/include -I $(LIBFT)
SRC		= main.c parser.c parser_utils.c parser_helpers.c parser_elements.c parser_objects.c \
		  vec_arithmetic.c vec_scaling.c vec_operations.c \
		  tuple_utils.c tuple_create.c math_utils.c \
		  mat_operations.c mat_inverse.c \
		  transforms.c transform_basic.c transform_rotate.c \
		  lighting.c lighting_components.c \
		  camera.c camera_controls.c render.c ray.c \
		  intersect.c intersect_cylinder.c intersect_cylinder2.c \
		  system_init.c normal.c error.c app_loop.c
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
