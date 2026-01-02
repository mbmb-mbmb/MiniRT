# Define the compiler
CC = cc

# Define the compiler flags
CFLAGS = -Wall -Wextra -Werror

# Define the target library
NAME = libft.a

# Define directories
PRINTF_DIR = ft_printf
PRINTF_LIB = $(PRINTF_DIR)/libftprintf.a

# Define the source files
SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
	   ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
	   ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
	   ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c \
	   ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
	   ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
	   ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_atoi2.c \
	   ft_free_ptr.c ft_free_array.c ft_arrlen.c ft_isnumber.c \
	   ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	   ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
	   ft_lstmap.c ft_atof.c

# Define the object files
OBJS = $(SRCS:.c=.o)

# Define the default rule
all: $(NAME)

# Create the static library
$(NAME): $(OBJS) $(PRINTF_LIB)
	cp $(PRINTF_LIB) $(NAME)
	ar rcs $(NAME) $(OBJS)

$(PRINTF_LIB):
	@make -C $(PRINTF_DIR)

# Rule to compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean up the build directory
clean:
	@make -C $(PRINTF_DIR) clean
	rm -f $(OBJS)

# Rule to clean up everything, including the target file
fclean: clean
	@make -C $(PRINTF_DIR) fclean
	rm -f $(NAME)

# Rule to rebuild everything from scratch
re: fclean all

# Rule to build and clean
.PHONY: all clean fclean re

