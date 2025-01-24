NAME=libft.a

.PHONY: all bonus re clean fclean

CC=cc

CFLAGS=-Wall -Wextra -Werror

FUNCTIONS=ft_atoi \
			ft_bzero \
			ft_calloc \
			ft_isalnum \
			ft_isalpha \
			ft_isascii \
			ft_isdigit \
			ft_isprint \
			ft_itoa	\
			ft_memchr \
			ft_memcmp \
			ft_memcpy \
			ft_memmove \
			ft_memset \
			ft_putchar_fd \
			ft_putendl_fd \
			ft_putnbr_fd \
			ft_putstr_fd \
			ft_split \
			ft_strchr \
			ft_strdup \
			ft_striteri \
			ft_strjoin \
			ft_strlcat \
			ft_strlcpy \
			ft_strlen \
			ft_strmapi \
			ft_strncmp \
			ft_strnstr \
			ft_strrchr \
			ft_strtrim \
			ft_substr \
			ft_tolower \
			ft_toupper \
			get_next_line \
			ft_printf \
			ft_ptr_handler \
			ft_putnumber_base \
			ft_isspace \
			ft_isupper \
			ft_islower \
			ft_strtol \
			ft_lstadd_back_bonus \
			ft_lstadd_front_bonus \
			ft_lstclear_bonus \
			ft_lstdelone_bonus \
			ft_lstiter_bonus \
			ft_lstlast_bonus \
			ft_lstnew_bonus \
			ft_lstsize_bonus \
			ft_lstmap_bonus \

all: $(NAME)

C_FILES=$(foreach func, $(FUNCTIONS), $(func).c)
O_FILES=$(foreach func, $(FUNCTIONS), $(func).o)

$(NAME): $(O_FILES)
	ar rcs $(NAME) $(O_FILES)

re: fclean all

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

clean:
	rm -f $(O_FILES)

fclean: clean
	rm -f $(NAME)
