/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:19:24 by flafi             #+#    #+#             */
/*   Updated: 2023/12/31 01:54:25 by flafi            ###   ########.fr       */
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

struct sigaction			g_sign;

// Token representing a pipe '|', assigned value 1
// Token representing '>', assigned default value (2)
// Token representing '>>', assigned de fault value (3)
// Token representing '<', assigned default value (4)
// Token representing '<<', assigned default value (5)
typedef enum s_token
{
	PIPE = 1,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
}							t_token;

typedef struct mem_block
{
	void					*block_pointer;
	int						type;
	struct mem_block		*next;
}							t_mem_block;

typedef struct s_mshell
{
	int						in_fd;
	int						out_fd;
	int						exit;
}							t_mshell;

typedef struct s_cmd
{
	char					**final_cmd;
	char					**final_arg;
	char					*input;
	char					*output;
	char					*output_ap;
	char					*here_doc;
	char					*flags;
	int						num_cmd;
}							t_cmd;

typedef struct s_lex
{
	char					*str;
	int						i;
	struct s_lex			*next;
	struct s_lex			*prev;
	t_token					token;
}							t_lex;

// Structure to represent a history entry
typedef struct s_historylist
{
	char					*command;
	struct s_historylist	*next;
	int						id;
}							t_historylist;

typedef struct s_cmd_inf
{
	struct s_parse			*parse;
	char					*command;
	char					**str;
	char					*cmd_name;
	struct s_lex			*list;
	int						pipe;
	int						in_fd;
	int						out_fd;
	t_mem_block				*lst;
	char					*input;
	char					**env;
	t_list					*envlst;
	char					*pwd;
	int						exp_flag;
	int						rtn_code;
	t_historylist			*history;
}							t_cmd_inf;

//*********************************//

int							ft_find_double(char *c, int index, int *q);
int							ft_find_single(char *c, int index, int *q);
int							ft_single_quote(char *c);
int							ft_double_qoute(char *c);
int							ft_quotes_both(char *str, int i);
//*********************************//
char						*ft_cmd(t_cmd_inf *c);
int							ft_check(int c);

int							ft_save_token(char *str, int i, t_lex **lex);
int							ft_save_other(char *str, int i, t_lex **lex);
int							ft_get_token(t_cmd_inf *cmd);

t_lex						*ft_lex_new(char *str, int token);
void						ft_lex_add(t_lex **lst, t_lex *new);
int							ft_add_node(char *str, t_token token, t_lex **list);

/*PIPEX*/
void						ft_free(char **str);
void						ft_error(void);
void						ft_child(char *cmd1, char **envp, int *fd);
void						ft_parent(char *cmd2, char **envp, int *fd);
char						*ft_getenv(const char *var_name, char **envp);
char						*ft_path(char *pathToFind, char **envp);
char						*ft_find(char *pathcopy, char **pathsegments,
								char *pathToFind);
void						ft_execve(char *argv, char **envp);
int							pipex(t_cmd *cmd, char **envp, int num_cmds);

// int pipex(char **cmds, char **envp);

void						*ft_malloc(t_mem_block **lst, int size);
void						*ft_calloc_s(size_t nelem, size_t elemsize,
								t_mem_block **lst);
char						*ft_strdup_s(const char *s, t_mem_block **lst);

/**************FIRAS*******************/
t_historylist				*ft_hstlast(t_historylist *lst);
/**************FIRAS*******************/
void						ft_addhst_back(t_historylist **history,
								t_historylist *new);
void						add_history_front(t_historylist **history,
								t_historylist *newEntry);
void						ft_add_history(const char *command,
								t_historylist **history, t_mem_block **lst);
/**************FIRAS*******************/
t_list						*fill_envlst(char **envp);
void						ft_init_envp(t_cmd_inf *c, char **envp);
void						signal_interrupt(int sig);
void						sigs(void);
/**************FIRAS*******************/
int							is_builtin(char **cmd, t_cmd_inf minish);
int							ft_export(char **cmd, t_cmd_inf minish);
int							ft_unset(char **cmd, t_cmd_inf minish);
void						ft_free_all(t_mem_block **lst);

/**************builtin*******************/
void						ft_dup2(int **fd, int i, int num_cmds);
void						ft_export_print(t_cmd_inf minish);
int							find_value(char *str);
int							check_alphanum(char *str);
char						*remove_qt(char *str);
int							ft_env(t_cmd_inf minish);
void						remove_quotes(char *str);
char						*rm_lastfld(char *cwd);
char						*get_cwd(void);
int							last_slash_pos(const char *str);
int							ft_echo(char **cmd, t_cmd_inf minish);
int							ft_pwd(char **cmd, char **env);
char						*ft_get_cd(char **cmd);
int							ft_cd(char **cmd, t_cmd_inf minish);
int							is_builtin(char **cmd, t_cmd_inf minish);
int							ft_run_builtin(t_cmd *cmd);

/**************helper*******************/
char						*ft_cmd(t_cmd_inf *c);
void						printf_hst(t_historylist *history);
int							ft_check(int c);
char						*ft_find(char *pathcopy, char **pathsegments,
								char *pathToFind);
char						*ft_path(char *pathToFind, char **envp);
void						free_string_array(char **array);
int							ft_free_fd(int **fd, int num_cmds);
int							ft_free_fdd(int **fd, int num_cmds);
void						ft_close_fd(int **fd, int num_cmds);
int							**ft_malloc_fd(int **fd, int num_cmds);
void						ft_read_write(t_cmd *cmds);
int							ft_open_here(t_cmd *cmds);
void						ft_read_red(t_cmd *cmds);
int							ft_heredoc(t_cmd *cmds, int fd);
t_lex						*ft_token_2(t_lex *list, t_cmd *cmd,
								t_mem_block *lst);
t_lex						*ft_token_3(t_lex *list, t_cmd *cmd,
								t_mem_block *lst);
t_lex						*ft_token_4(t_lex *list, t_cmd *cmd,
								t_mem_block *lst);
t_lex						*ft_token_5(t_lex *list, t_cmd *cmd,
								t_mem_block *lst);
t_lex						*ft_all_token(t_lex *list, t_cmd *cmd,
								t_mem_block *lst);
t_cmd						*create_cmd_structure(int cmd_size, int arg_size,
								t_mem_block *lst);
pid_t						my_getpid(void);
int							check_exist_envp(char *var_name, t_cmd_inf minish);

#endif