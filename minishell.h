/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:19:24 by flafi             #+#    #+#             */
/*   Updated: 2023/12/10 20:34:26 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
# include "./libft/libft.h"
// ANSI color escape codes
# define ANSI_COLOR_RED "\x1b[31m"
# define ANSI_COLOR_GREEN "\x1b[32m"
# define ANSI_COLOR_YELLOW "\x1b[33m"
# define ANSI_COLOR_BLUE "\x1b[34m"
# define ANSI_COLOR_RESET "\x1b[0m"

typedef struct mem_block
{
	void				*block_pointer;
	struct mem_block	*next;
}						t_mem_block;

// Structure to represent a history entry
typedef struct s_historylist
{
    char			 *command;
    struct s_historylist *next;
} t_historylist;

typedef struct	s_mini
{
    char test;
} t_mini;
// typedef struct s_list
// {
// 	// t_type			type;
// 	struct s_list	*next;
// 	struct s_list	*prev;
// 	char			*content;
// }	t_list;

// typedef struct s_glob
// {
// 	char** 	env
// }						t_glob;

void	*ft_malloc(t_mem_block **lst, int size);
void	ft_free_all(t_mem_block **lst);
char	*ft_strdup_s(const char *s, t_mem_block **lst);
#endif