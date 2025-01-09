NAME := fdf 

CC := cc 
CFLAGS := -Wall -Wextra -Werror
# -Wunreachable-code -Ofast
RM := rm -rf

# MLX library
LIBMLX_URL := https://github.com/codam-coding-college/MLX42.git
LIBMLX_DIR := ./lib/MLX42
LIBMLX := $(LIBMLX_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm
LIB_DIR := lib/libft
INCLUDE := -I$(LIB_DIR) -I./include/ -I./lib/MLX42/include/MLX42/
WITH_LIBFT := -L$(LIB_DIR) -lft
SRCS := src/main.c \
	src/math_ops.c \
	src/parsing.c \
	src/utils.c \
	src/validation.c \


OBJS = $(SRCS:.c=.o)

#TODO: final look
all: clone libft $(NAME)
	./$(NAME) test_maps/elem-col.fdf
#	valgrind ./$(NAME) ~/Downloads/test_maps/42.fdf

clone: lib/MLX42

lib/MLX42:
	git clone $(LIBMLX_URL) $(LIBMLX_DIR)
	
$(NAME): $(OBJS)
	cmake $(LIBMLX_DIR) -B $(LIBMLX_DIR)/build && make -C $(LIBMLX_DIR)/build -j4
	$(CC) $^ $(LIBMLX) $(WITH_LIBFT) -o $@

libft:
	make -C $(LIB_DIR) bonus

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) $< -c -o $@

clean:
	@$(RM) $(OBJS)

fclean: clean
	@make fclean -C $(LIB_DIR)
	@$(RM) $(LIBMLX_DIR)/build
	@$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re clone libft
