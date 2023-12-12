# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flafi <flafi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/01 16:40:23 by flafi             #+#    #+#              #
#    Updated: 2023/12/12 17:38:34 by flafi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEF_COLOR = \033[0;39m
RED = \033[0;91m
GREEN = \033[0;32m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

.SILENT:
NAME = minishell
CFLAGS = -Wall -Wextra -Werror 
LIB = -lreadline
LIBFT = libft/libft.a
CC = cc

SRCS = minishell.c ./utils/garbage_collector.c ft_strdup_s.c ./builtins/builtin.c
OBJS = $(SRCS:.c=.o)




all: $(NAME) $(LIBFT)

$(NAME): $(OBJS) 
	make -C libft
	cc $(SRCS) -o $(NAME) $(LIBFT) $(CFLAGS) $(LIB)
	echo "$(GREEN)Minishell Compiled$(DEF_COLOR)"



clean:
	rm -f $(OBJS)
	make -C libft clean
	echo "$(RED)Object Files are deleted$(DEF_COLOR)"

fclean: clean
	rm -rf $(NAME)
	make -C libft fclean
	echo "Everything is clean"

re: fclean all

.PHONY: all clean fclean re