NAME := fdf 

GREEN = \033[1;92m
DEFAULT = \033[1;39m

CC = cc 
CFLAGS := -Wall -Wextra -Werror
#-Wunreachable-code -Ofast
RM := rm -rf

# MLX library
LIBMLX_URL := https://github.com/codam-coding-college/MLX42.git
LIBMLX_DIR := ./lib/MLX42
LIBMLX := $(LIBMLX_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm

#TODO: add libft versioning and cloning rules
# Libft library
LIB_DIR:= lib/libft
LIB_URL := https://github.com/mikhailbish/libft.git
LIBFT_A := $(LIB_DIR)/libft.a

HEADERS := -I. -I $(LIBMLX_DIR)/include -I$(LIB_DIR)

# mandatory srcs
SRCS = main.c utils.c validation.c parsing.c math_ops.c
#SRCS = test.c

OBJS = $(SRCS:.c=.o)

# TODO: remove logging in the end
LOG_NAME = $(shell date -Iseconds)

all: clone $(NAME)
	./$(NAME) ~/Downloads/test_maps/42.fdf
#	./$(NAME) test_maps/elem-col.fdf >> ./logs/$(LOG_NAME)

clone: lib/MLX42 lib/libft # .clone_mlx_done .clone_lib_done

# "! -d" means if the directory doesn't exist.
lib/MLX42:
	git clone $(LIBMLX_URL) $(LIBMLX_DIR); 
	
lib/libft:
	git clone $(LIB_URL) $(LIB_DIR); 

$(NAME): $(OBJS)
	@cmake $(LIBMLX_DIR) -B $(LIBMLX_DIR)/build && make -C $(LIBMLX_DIR)/build -j4
	@make -C $(LIB_DIR) bonus
	@$(CC) $^ $(LIBMLX) $(LIBFT_A) -o $@
	@echo "$(GREEN)$(NAME) has been generated successfully!$(DEFAULT)"

%.o: %.c
	@$(CC) $(CFLAGS) $(HEADERS) $< -D BUFFER_SIZE=6000 -c -o $@

# TODO: add cleaning of mlx
clean:
	@make fclean -C $(LIB_DIR)
	@$(RM) $(LIBMLX_DIR)/build
	@$(RM) $(OBJS)
#	temp block to prevent unnecessary downloading
#	@rm -rf lib/libft

fclean: clean
	@$(RM) $(NAME)
	@echo "$(GREEN)$(NAME) executable file has been cleaned.$(DEFAULT)"
#	temp block to prevent unnecessary downloading
#	@$(RM) lib

re:	fclean all

.PHONY: all clean fclean re clone
