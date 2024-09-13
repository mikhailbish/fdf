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
SRCS = main.c parser.c utils.c 

OBJS = $(SRCS:.c=.o)


all: clone $(NAME)
	./$(NAME)

# .clone_done will be generated as a hidden file, and it will contain the timestamp
# to tell if the target is latest or not. So the execute 'make' command at the second
# time, it will show "make: nothing to be done for 'all'"
clone: lib/MLX42 lib/libft # .clone_mlx_done .clone_lib_done

# "! -d" means if the directory doesn't exist.
lib/MLX42:
	git clone $(LIBMLX_URL) $(LIBMLX_DIR); 
	
lib/libft:
	git clone $(LIB_URL) $(LIB_DIR); 

$(NAME): $(OBJS)
	@cmake $(LIBMLX_DIR) -B $(LIBMLX_DIR)/build && make -C $(LIBMLX_DIR)/build -j4
	@make -C $(LIB_DIR)
	@$(CC) $^ $(LIBMLX) $(LIBFT_A) -o $@
	@echo "$(GREEN)$(NAME) has been generated successfully!$(DEFAULT)"

%.o: %.c
	@$(CC) $(CFLAGS) $(HEADERS) $< -c -o $@ && printf "Compiling: $(notdir $<)"

clean:
	@make clean -C $(LIB_DIR)
	@$(RM) $(OBJS)
	@$(RM) $(LIBMLX_DIR)
	@rm -rf lib/libft

fclean: clean
	@$(RM) lib
	@$(RM) $(NAME)
	@echo "$(GREEN)so_long executable file has been cleaned.$(DEFAULT)"

re:	fclean all

.PHONY: all clean fclean re clone
