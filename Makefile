# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flafi <flafi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/01 16:40:23 by flafi             #+#    #+#              #
#    Updated: 2023/12/02 19:01:19 by flafi            ###   ########.fr        #
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
CC = cc

SRCS = minishell.c ./utils/garbage_collector.c
OBJS = $(SRCS:.c=.o)



$(NAME): $(OBJS) 
	cc  $(SRCS) -o $(NAME) $(CFLAGS)
	echo "$(GREEN)Minishell Compiled$(DEF_COLOR)"

all: $(NAME)



clean:
	rm -f $(OBJS)
	echo "$(RED)Object Files are deleted$(DEF_COLOR)"

fclean: clean
	rm -rf $(NAME)
	echo "Everything is clean"

re: fclean all

.PHONY: all clean fclean re