NAME = libft.a
CFLAGS = -Wall -Wextra -Werror
CC = cc

SRCS = ft_atoi.c ft_toupper.c ft_tolower.c ft_bzero.c ft_isalnum.c 	ft_isalpha.c ft_isascii.c ft_isprint.c \
		ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memset.c ft_strchr.c ft_strlcpy.c ft_isdigit.c \
		ft_strlen.c ft_strrchr.c ft_strncmp.c ft_strlcat.c ft_memmove.c ft_strnstr.c ft_calloc.c \
		ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
		ft_putnbr_fd.c ft_itoa.c ft_strmapi.c ft_striteri.c \
		 ft_split.c gnl.c

OBJS = $(SRCS:.c=.o)

SRCS_B = ft_lstnew.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstadd_front.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJS_B = $(SRCS_B:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

bonus: $(OBJS_B)
	@ar rcs $(NAME) $(OBJS_B)

$(OBJS):%.o:%.c ft_*.c
	@$(CC) $(CFLAGS) -c $< -o $@

fclean:
	rm -rf *.o
	rm -rf $(NAME)
clean:
	rm -rf $(OBJS) $(OBJS_B)
re: fclean all