/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:19:24 by flafi             #+#    #+#             */
/*   Updated: 2023/12/23 18:35:06 by flafi            ###   ########.fr       */
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

struct sigaction g_sign;

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
    int id;
} t_historylist;

typedef struct	s_mini
{
    char **env;
    t_list *envlst;
    char *pwd;
    int exp_flag;
    int rtn_code;
} t_mini;




void	*ft_malloc(t_mem_block **lst, int size);
void	ft_free_all(t_mem_block **lst);
char	*ft_strdup_s(const char *s, t_mem_block **lst);
int     is_builtin(char **cmd, t_mini minish);
void ft_export(char **cmd, t_mini minish);
void ft_env(t_mini minish);
int find_value(char *str);
void ft_unset(char **cmd, t_mini minish);
void printf_hst(t_historylist *history);
#endif