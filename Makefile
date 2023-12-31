# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flafi <flafi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/01 16:40:23 by flafi             #+#    #+#              #
#    Updated: 2023/12/31 04:28:54 by flafi            ###   ########.fr        #
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
CC = gcc

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_INC = -I$(LIBFT_DIR)

# Include paths for readline
READLINE_INC = -I /usr/include/readline
READLINE_LIB = -lreadline -lhistory

SRCS = minishell.c\
./utils/garbage_collector.c\
./utils/token_related.c\
./utils/mini_utils.c\
./utils/helper.c\
./init/ft_quote.c\
./init/ft_handle_token.c\
./init/ft_add_lex.c\
./pipex/pipex.c\
./pipex/pipex_utils.c\
./pipex/find_path.c \
./pipex/fd_related.c \
./pipex/dup.c \
./get_envp/ft_strdup_s.c\
./get_envp/ft_history.c\
./get_envp/sigs.c\
./builtins/builtin.c\
./builtins/builtin_utils2.c\
./builtins/export.c\
./builtins/unset.c\
./builtins/export_utils.c\
./builtins/builtin_utils.c\

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) -o $(NAME) $(CFLAGS) $(LIBFT) $(READLINE_LIB)
	echo "$(GREEN)Minishell Compiled$(DEF_COLOR)"

all: $(NAME)

clean:
	rm -f $(OBJS)
	echo "$(RED)Object Files are deleted$(DEF_COLOR)"
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME)
	echo "$(RED)Everything is clean$(DEF_COLOR)"
	make -C $(LIBFT_DIR) fclean

re: fclean all

$(LIBFT):
	make -C $(LIBFT_DIR)

.PHONY: all clean fclean re
