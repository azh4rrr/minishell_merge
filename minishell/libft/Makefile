CC = cc
CFLAGS = -Wall -Wextra -Werror #~-fsanitize=address
NAME = libft.a

SRCS =		ft_strlen.c		ft_strdup.c		\
			ft_strjoin.c	ft_memcpy.c		\
			ft_substr.c		ft_strncpy.c	\
			ft_isalpha.c	ft_strcmp.c		\
			ft_isdigit.c	ft_isalnum.c	\
			ft_strchr.c		ft_split.c		\
			ft_putstr_fd.c	ft_putchar_fd.c	\
			ft_atoi.c		ft_itoi.c		\
			is_space.c		ft_strlcpy.c	\
			ft_strcpy.c		ft_strcat.c 	\

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $@ $(OBJS)

%.o: %.c libft.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
