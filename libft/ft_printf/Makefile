CC = cc
CFLAGS = -Wall -Werror -Wextra

SRCS = \
ft_printf.c \
print_hex.c \
print_int.c \
print_uint.c \
print_char.c \
print_str.c \
print_ptr.c

OBJS = $(SRCS:.c=.o)

LIBRARY = libftprintf.a

all: $(LIBRARY)

$(LIBRARY): $(OBJS)
	ar rcs $(LIBRARY) $(OBJS)

%.o: %.c ft_print.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(LIBRARY)

re: fclean all

.PHONY: all clean fclean re
