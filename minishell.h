/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:19:24 by flafi             #+#    #+#             */
/*   Updated: 2023/12/29 10:21:19 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>

// ANSI color escape codes
# define ANSI_COLOR_RED "\x1b[31m"
# define ANSI_COLOR_GREEN "\x1b[32m"
# define ANSI_COLOR_YELLOW "\x1b[33m"
# define ANSI_COLOR_BLUE "\x1b[34m"
# define ANSI_COLOR_RESET "\x1b[0m"

struct sigaction g_sign;

typedef enum s_token
{
    PIPE = 1,        // Token representing a pipe '|', assigned value 1
    GREAT,           // Token representing '>', assigned default value (2)
    GREAT_GREAT,     // Token representing '>>', assigned default value (3)
    LESS,            // Token representing '<', assigned default value (4)
    LESS_LESS,       // Token representing '<<', assigned default value (5)
} t_token;          // Alias the enumeration as 't_token'

typedef struct mem_block
{
	void				*block_pointer;
	int					type;//To test env allocations
	struct mem_block	*next;
}						t_mem_block;

typedef struct s_mshell
{
	int					in_fd;
	int					out_fd;
	int					exit;
}						t_mshell;

typedef struct s_cmd
{	
	char  **final_cmd;
	char  **final_arg;
	char  *input;
	char  *output;
	char  *output_ap;
	char *here_doc;
	int flag_input;
	int flag_output;
	int   token;
}						t_cmd;


typedef struct s_lex
{	
	char 		    	*str;
	int                   i;
    struct s_lex         *next;
    struct s_lex         *prev;
	t_token			    token;
}						t_lex;


// Structure to represent a history entry
typedef struct s_historylist
{
    char			 *command;
    struct s_historylist *next;
    int id;
} t_historylist;

typedef struct s_cmd_inf
{
	char	                 *command;
    char **str;
    char *cmd_name;
	struct  s_lex            *list;
	struct	s_parse          *parse;
	int		                  pipe;
    int in_fd;
    int out_fd;
	// firas
	char **env;
    t_list *envlst;
    char *pwd;
    int exp_flag;
    int rtn_code;
	t_mem_block		*lst;
	t_historylist	*history;
	
}				t_cmd_inf;



//*********************************//

int		ft_find_double(char *c, int index, int *q);
int		ft_find_single(char *c, int index, int *q);
int		ft_single_quote(char *c);
int		ft_double_qoute(char *c);
int		ft_quotes_both(char *str, int i);
//*********************************//
char	*ft_cmd(t_cmd_inf *c);
int		ft_check(int c);

int	ft_save_token(char *str, int i, t_lex **lex);
int	ft_save_other(char *str, int i, t_lex **lex);
int	ft_get_token(t_cmd_inf *cmd);

t_lex	*ft_lex_new(char *str, int token);
void	ft_lex_add(t_lex **lst, t_lex *new);
int	ft_add_node(char *str, t_token token, t_lex **list);

/*PIPEX*/
void	ft_free(char **str);
void	ft_error(void);
void ft_child(char *cmd1, char **envp, int *fd);
void ft_parent(char *cmd2, char **envp, int *fd);
char	*ft_getenv(const char *var_name, char **envp);
char	*ft_path(char *pathToFind, char **envp);
char	*ft_find(char *pathcopy, char **pathsegments, char *pathToFind);
void	ft_execve(char *argv, char **envp);
int	pipex(t_cmd *cmd, char **envp, int num_cmds,int index);


// int pipex(char **cmds, char **envp);


void	*ft_malloc(t_mem_block **lst, int size);

/**************FIRAS*******************/
void	*ft_calloc_s(size_t nelem, size_t elemsize, t_mem_block **lst);
char	*ft_strdup_s(const char *s, t_mem_block **lst);
/**************FIRAS*******************/
t_historylist	*ft_hstlast(t_historylist *lst);
void	ft_addhst_back(t_historylist **history, t_historylist *new);
void	add_history_front(t_historylist **history, t_historylist *newEntry);
void	ft_add_history(const char *command, t_historylist **history,t_mem_block **lst);
/**************FIRAS*******************/
t_list	*fill_envlst(char **envp);
void	ft_init_envp(t_cmd_inf *c, char **envp);
void	signal_interrupt(int sig);
void	sigs(void);
/**************FIRAS*******************/
int	is_builtin(char **cmd, t_cmd_inf minish);
void ft_export(char **cmd, t_cmd_inf minish);
void ft_unset(char **cmd, t_cmd_inf minish);

#endif