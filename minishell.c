/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelhaj- <mbelhaj-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:19:21 by flafi             #+#    #+#             */
/*   Updated: 2023/12/30 07:47:16 by mbelhaj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char *ft_cmd(t_cmd_inf *c)
{
    char *input;
    char **token;

    input = readline(ANSI_COLOR_GREEN "MyShell$ " ANSI_COLOR_RESET);
    if (input == NULL)
            return (NULL); // Exit the loop if input is NULL (EOF or error)
    if (input[0] != '\0')
    {
        token = ft_split(input, ' ');
            add_history(input);
            token = history_tokenize(input);
            ft_add_history(input, &c->history, &c->lst);
            // free(input);
    }

    // Corrected usage of rl_replace_line to reset the prompt without ANSI codes
    rl_replace_line("", 0);
    rl_redisplay();
    // rl_on_new_line();
	c->input = ft_strdup(input);
	free(input);
    return (c->input);
}

int	ft_check(int c)
{
	if (c == '|')
		return (PIPE);
	else if (c == '>')
		return (GREAT);
	else if (c == '<')
		return (LESS);
	return (0);
}


t_cmd	*create_cmd_structure(int cmd_size, int arg_size, t_mem_block *lst)
{
	t_cmd	*cmd;

	cmd = ft_malloc(&lst, sizeof(t_cmd));
	if (!cmd)
	{
		perror("Memory allocation error");
	}
	cmd->final_cmd = ft_malloc(&lst, sizeof(char *) * cmd_size);
	cmd->final_arg = ft_malloc(&lst,sizeof(char *) * arg_size);
	cmd->input = ft_malloc(&lst,sizeof(char *) * arg_size);
	cmd->output = ft_malloc(&lst,sizeof(char *) * arg_size);
	cmd->flags = ft_malloc(&lst, sizeof(char *) * arg_size);
	if (!cmd->final_cmd || !cmd->final_arg)
	{
		perror("Memory allocation error");
	}
	cmd->input = NULL;
	cmd->output = NULL;
	cmd->flags = ft_strdup_s("", &lst);
	return (cmd);
}


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


// void	handle_dolla(t_mini *minish, char **token)
// {
// 	int	i;
// 	int	j;

// 	(void)minish;
// 	j = 0;
// 	i = 0;
// 	while (token[i])
// 	{
// 		if (ft_strchr(token[i], '$') != NULL)
// 		{
// 			while (token[i][j])
// 			{
// 				if (token[i][j] == '$' && token[i][j + 1] && token[i][j
// 					+ 1] == '$')
// 				{
// 					printf("%i", getpid());
// 					j++;
// 				}
// 				else
// 				{
// 					check_exist_envp(token[i], *minish);
// 					j++;
// 				}
// 				j++;
// 			}
// 			j = 0;
// 		}
// 		i++;
// 	}
// 	// printf("MyShell : %i\n", minish->rtn_code);
// }


int	ft_check_red(int index)
{
	if (index == 1)
		return (1);
	else if (index == 2)
		return (2);
	else if (index == 3)
		return (3);
	else if (index == 4)
		return (4);
	else if (index == 5)
		return (5);
	else
		return (0);
}

void	ft_parsing(t_lex *list, t_cmd *cmd, char **envp)
{
	int	i;
	int	j;
	int	k;
	
	t_mem_block *lst = NULL;
	i = -1;
	j = 0;
	while (list != NULL)
	{
		if (list->str == NULL)
		{
		    if (list->token == 2)
			{
				list = list->next;
				cmd->output = ft_strdup_s(list->str, &lst);
				cmd->flags = ft_strjoin(cmd->flags,"G");
				list = list->next;
			}
            else if (list->token == 3)
			{
				list = list->next;
				cmd->output = ft_strdup_s(list->str, &lst);
                cmd->flags = ft_strjoin(cmd->flags,"G_G");
				list = list->next;
			}
            else if (list->token == 4)
			{
				list = list->next;
				cmd->input = ft_strdup_s(list->str, &lst);
                cmd->flags = ft_strjoin(cmd->flags,"L");
				list = list->next;
			}
            else if (list->token == 5)
			{
				list = list->next;
				cmd->here_doc = ft_strdup_s(list->str, &lst);
                cmd->flags = ft_strjoin(cmd->flags,"L_L");
				list = list->next;
			}
			else
				list = list->next;
		}
		else
		{
			i++;
			cmd->final_cmd[i] = ft_strdup_s(list->str, &lst);
			// printf("new cmd %s\n", cmd->final_cmd[i]);
			list = list->next;
			while (list != NULL && list->str != NULL)
			{
				cmd->final_arg[j] = ft_strdup_s(list->str, &lst);
				cmd->final_cmd[i] = ft_strjoin(cmd->final_cmd[i], " ");
				cmd->final_cmd[i] = ft_strjoin(cmd->final_cmd[i],
					cmd->final_arg[j]);
				// printf("full CMD number %i = %s\n", i, cmd->final_cmd[i]);
				j++;
				list = list->next;
			}
		}
	}

	k = 0;
	while (k < i + 1)
	{
		// printf("CMD ----------->> %s\n", cmd->final_cmd[k]);
		k++;
	}
	// printf("flags ----------->> %s\n",cmd->flags);
	// execute_command(cmd,envp);
	 pipex(cmd,envp,k);
	//  ft_free_all(&lst);
	//  ft_rest();
// 	free_cmd_structure(cmd, k, j);
}

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
void	free_split(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
void	minishell_loop(t_cmd_inf c, char **envp)
{
	char	*cmd;
	t_cmd	*token;
	int		i;

	// token = create_cmd_structure(100, 100);
	i = 0;
	while (1)
	{
		cmd = ft_cmd(&c);
		if (!cmd)
		{
			free(cmd);
			exit(0);
		}
		t_mem_block *lst = NULL;
		token = create_cmd_structure(10, 10, lst);
		c.command = ft_strtrim(cmd, " ");
		//  if (c.input)
		// 		free(c.input);
		// printf("result 1  %s\n", c.command);
		if (!ft_double_qoute(c.command))
			printf("no double quote \n");
		if (!ft_single_quote(c.command))
			printf("no signle quote \n");
		if (!ft_get_token(&c))
			printf("\nOKAY\n");
		ft_parsing(c.list, token, envp);
		if (token->final_cmd != NULL && *token->final_cmd != NULL)
		{
			if (is_builtin(token->final_cmd, c) == 0)
				;
			if (ft_strncmp(token->final_cmd[0], "history", 7) == 0)
				printf_hst(c.history);
			// else
			// {
			// 	run_cmd(token);
			// }
			free(token);
		}
		else if (token != NULL)
		{
			free(token); // Free memory for an empty token
		}
		// ft_free_all(c.lst);
		ft_free_all(&lst);
		// free(token->input);
		// free(token->output);
		// // free(token->here_doc);
		// free(token->flags);
		// free_split(token->final_cmd);
		// free_split(token->final_arg);
		// printf("input  = %s\n", token->input);
		// printf("OUTPUT  = %s\n", token->output);
		// ft_red(token);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd_inf	c;

	ft_init_envp(&c, envp);
	if (argv[1] || argc != 1)
	{
		printf("ERROR");
		exit(0);
	}
	sigs();
	minishell_loop(c, envp);
	rl_clear_history();
	return (0);
}
