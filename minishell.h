/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelhaj- <mbelhaj-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:19:24 by flafi             #+#    #+#             */
/*   Updated: 2023/12/14 22:45:18 by mbelhaj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/history.h>
# include <readline/readline.h>

typedef struct mem_block
{
	void				*block_pointer;
	struct mem_block	*next;
}						t_mem_block;

typedef struct s_mshell
{
	int					in_fd;
	int					out_fd;
	int					exit;
}						t_mshell;


typedef struct s_cmd_inf
{
	char	*command;
	int		len;
}				t_cmd_inf;

int	ft_find_double(char *c, int index, int *q);
int	ft_find_single(char *c, int index, int *q);
int	ft_single_quote(char *c);
int	ft_double_qoute(char *c);



#endif