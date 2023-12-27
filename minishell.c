/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:19:21 by flafi             #+#    #+#             */
/*   Updated: 2023/12/26 21:31:23 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

t_historylist	*ft_hstlast(t_historylist *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}
void	ft_addhst_back(t_historylist **history, t_historylist *new)
{
	t_historylist	*last;

	if (history)
	{
		if (*history)
		{
			last = ft_hstlast(*history);
			last->next = new;
		}
		else
			*history = new;
	}
}
void	add_history_front(t_historylist **history, t_historylist *newEntry)
{
	// Add the entry to the front of the list
	ft_addhst_back(history, newEntry);
}

// Create a new history entry & add to the front of the list
void	ft_add_history(const char *command, t_historylist **history,
		t_mem_block **lst)
{
	t_historylist	*newEntry;

	newEntry = ft_malloc(lst, sizeof(t_historylist));
	// do a rework for strdup or add to the lst free
	newEntry->command = ft_strdup_s(command, lst);
	newEntry->next = NULL;
	add_history_front(history, newEntry);
}
// t_historylist *history = NULL;
void	printf_hst(t_historylist *history)
{
	int				index;
	t_historylist	*current;

	index = 0;
	current = history;
	while (current != NULL)
	{
		printf("%d %s\n", index++, current->command);
		current = current->next;
	}
}

// call ft_add_history(input, &history, &lst);
/* above is pointless*/ /* above is pointless*/
/* above is pointless*/ /* above is pointless*/

char	**make_encpy(char **envp, t_mem_block *lst)
{
	int		envp_size;
	char	**envcpy;
	int		i;

	envp_size = 0;
	while (envp[envp_size])
	{
		envp_size++;
	}
	envcpy = ft_malloc(&lst, (envp_size + 1) * sizeof(char *));
	// Allocate memory for envcpy
	if (envcpy == NULL)
	{
		printf("Memory allocation failed\n");
		exit(1);
	}
	i = 0;
	while (envp[i])
	{
		// Allocate memory for each environment variable and copy its content
		envcpy[i] = ft_strdup_s(envp[i], &lst);
		i++;
	}
	envcpy[i] = NULL;
	return (envcpy);
}
// change it later to ft malloc for leaks
t_list	*fill_envlst(char **envp)
{
	int		i;
	t_list	*envlst;

	i = 1;
	envlst = ft_lstnew(envp[0]);
	// printf("content of the first lst = %s\n", envlst->content);
	while (envp[i])
	{
		ft_lstadd_back(&envlst, ft_lstnew(envp[i]));
		i++;
	}
	return (envlst);
}
/*pipex*/ /*pipex*/ /*pipex*/ /*pipex*/ /*pipex*/ /*pipex*/ /*pipex*/
// checking for excuting permissions and return path
char	*ft_check_x(char **array, char **cmd1)
{
	int		i;
	char	*path;

	path = NULL;
	i = 0;
	while (array[i])
	{
		array[i] = ft_strjoin(array[i], "/");
		array[i] = ft_strjoin(array[i], *cmd1);
		if (access(array[i], X_OK) == 0)
		{
			path = array[i];
			break ;
		}
		else
			i++;
	}
	if (!path)
	{
		// ft_error("no path");
		printf("no path");
	}
	return (path);
}
// char	*check_x_abs(void)
// {

// }
void	run_cmd(char **cmd)
{
	char	**array;
	char	*path;
	char	**args;
	char	*argslst;
	int		i;
	char	*argsv[];

	array = ft_split(getenv("PATH"), ':');
	args = NULL;
	argslst = ft_strdup("");
	i = 1;
	if (cmd[0][0] == '/')
	{
		if (access(cmd[0], X_OK) == 0)
			path = cmd[0];
		else
			printf("no access or invalid\n");
	}
	else
	{
		path = ft_check_x(array, cmd);
	}
	while (cmd[i])
	{
		argslst = ft_strjoin(argslst, cmd[i]);
		if (cmd[i + 1])
			argslst = ft_strjoin(argslst, " ");
		i++;
	}
	if (ft_strlen(argslst) > 1)
	{
		// printf("args =  %s\n", argslst);
		args = ft_split(argslst, ' ');
	}
	else
	{
		// memory issue here
		args = malloc(1 * sizeof(char *));
		args[0] = ft_strdup("");
	}
	// printf("path = %s\n", path);
	// printf("arglst = %s\n", argslst);
	// fix ENVP 111!!!!
	// this is for tesitngs
	//  CMD then FLAGS then NULL
	argsv[] = {cmd[0], "-a", NULL};
	execve(path, argsv, NULL);
}
void	run_pipes(int fd[2], char **commands, int n)
{
	int	i;
	int	pid;
	int	status;
	int	in_fd;

	i = 0;
	in_fd = 0;
	while (i < n)
	{
		if (i < n - 1)
			pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			if (in_fd != 0)
			{
				dup2(in_fd, 0);
				close(in_fd);
			}
			if (i < n - 1)
			{
				close(fd[0]);
				dup2(fd[1], 1);
				close(fd[1]);
			}
			run_cmd(commands);
			exit(EXIT_FAILURE);
		}
		else
		{
			if (in_fd != 0)
				close(in_fd);
			if (i < n - 1)
			{
				close(fd[1]);
				in_fd = fd[0];
			}
			waitpid(pid, &status, 0);
		}
		i++;
	}
}
/*pipex*/ /*pipex*/ /*pipex*/ /*pipex*/ /*pipex*/ /*pipex*/ /*pipex*/
// sigs
void	signal_interrupt(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		exit(EXIT_SUCCESS);
}
void	sigs(void)
{
	// rl_catch_signals = 0;
	g_sign.sa_handler = signal_interrupt;
	g_sign.sa_flags = 0;
	sigaction(SIGINT, &g_sign, NULL);
	sigaction(SIGQUIT, &g_sign, NULL);
	// rl_clear_signals();
}
// sigs

// pipes
void	create_pipes(int pipes[][2], int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("Pipe creation failed");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

// strchr for token 2d
int	ft_strchr_2d(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (ft_strchr(array[i], '$') != NULL)
			return (1);
		i++;
	}
	return (0);
}

// check if exists
int	check_exist_envp(char *var_name, t_mini minish)
{
	t_list	*current;
	char	*lol;

	current = minish.envlst;
	var_name++;
	while (current)
	{
		if (ft_strncmp(var_name, current->content, ft_strlen(var_name)) == 0)
		{
			lol = ft_substr(current->content, ft_strlen(var_name) + 2,
				ft_strlen(current->content) - ft_strlen(var_name));
			printf("%s", lol);
			free(lol);
			return (0);
		}
		current = current->next;
	}
	return (1);
}

void	handle_dolla(t_mini *minish, char **token)
{
	int	i;
	int	j;

	(void)minish;
	j = 0;
	i = 0;
	while (token[i])
	{
		if (ft_strchr(token[i], '$') != NULL)
		{
			while (token[i][j])
			{
				if (token[i][j] == '$' && token[i][j + 1] && token[i][j
					+ 1] == '$')
				{
					printf("%i", getpid());
					j++;
				}
				else
				{
					check_exist_envp(token[i], *minish);
					j++;
				}
				j++;
			}
			j = 0;
		}
		i++;
	}
	// printf("MyShell : %i\n", minish->rtn_code);
}

// look for env variables and change them in the print of intereption
int	main(int argc, char **argv, char **envp)
{
	char			*input;
	t_mem_block		*lst;
	char			**token;
	t_historylist	*history;
	t_mini			minish;
	char			**envcpy;

	lst = NULL;
	history = NULL;
	// init struct idk how many things
	minish.env = envp;
	minish.envlst = fill_envlst(envp);
	minish.exp_flag = 0;
	minish.rtn_code = 0;
	// system("leaks minishell");
	(void)argv;
	if (argc != 1)
	{
		printf("error\n");
		exit(1);
	}
	//  testing here
	// int pipes[2][2];
	envcpy = make_encpy(envp, lst);
	(void)envcpy;
	sigs();
	while (1)
	{
		input = readline(ANSI_COLOR_GREEN "MyShell$ " ANSI_COLOR_RESET);
		if (input == NULL)
			break ; // Exit the loop if input is NULL (EOF or error)
		if (input[0] != '\0')
		{
			add_history(input);
			token = history_tokenize(input);
			ft_add_history(input, &history, &lst);
			free(input);
			if (token != NULL && *token != NULL)
			{
				// printf("cmd = %s\n", *token);
				// char *vv[] = {"", NULL};
				// execve("/usr/bin/uname", vv, envp);
				if (is_builtin(token, minish) == 0)
					;
				else if (ft_strncmp(token[0], "history", 7) == 0)
					printf_hst(history);
				else if (ft_strchr_2d(token) == 1)
				{
					// temp until mo moves it
					// fill the commands withteh code an the failed one with their appropriate
					handle_dolla(&minish, token);
				}
				else
				{
					// handle excution with absolute and relative path
					// create_pipes(pipes, 2);
					// run_pipes(pipes[0] ,token, 2);
					run_cmd(token);
				}
				free(token);
			}
			else if (token != NULL)
			{
				free(token); // Free memory for an empty token
			}
		}
		else
		{
			free(input); // Free memory for an empty input
		}
	}
	ft_free_all(&lst);
	return (0);
}
