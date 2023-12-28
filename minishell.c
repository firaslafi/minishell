/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:19:21 by flafi             #+#    #+#             */
/*   Updated: 2023/12/28 05:35:22 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	*ft_cmd(t_cmd_inf *c)
{
	char	*input;
	char	**token;

	// firas
	input = readline(ANSI_COLOR_GREEN "MyShell$ " ANSI_COLOR_RESET);
	token = ft_split(input, ' ');
	if (input == NULL)
		return (NULL); // Exit the loop if input is NULL (EOF or error)
	if (input[0] != '\0')
	{
		add_history(input);
		token = history_tokenize(input);
		ft_add_history(input, &c->history, &c->lst);
		free(input);
	}
	// firas
	// rl_bind_key('\t', rl_insert);
	// cmd = readline("minishell >");
	// if (!cmd)
	// 	printf("\nExiting...\n");
	// if (cmd[0] != '\0')
	// 	add_history(cmd);
	return (input);
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

// int	ft_get_cmd(t_token *tokens, t_env *env)
// {
// 	t_token	*head;

// 	head = tokens;
// 	if (qcheck(tokens) == -1)
// 		return (-1);
// 	while (head)
// 	{
// 		if (head->operation == CMD && !head->table)
// 		{
// 			if (cmd_maker(head) == -1)
// 				return (-1);
// 		}
// 		else if (head->operation == REDIRECT)
// 		{
// 			if (handling(head) == -1)
// 				return (-1);
// 		}
// 		else if (head->operation == HERE_DOC)
// 		{
// 			if (h_doc(tokens, env) == -1)
// 				return (-1);
// 		}
// 		head = head->next;
// 	}
// 	return (0);
// }

// /// @brief Creates a command structure (t_command)
// /// and populates it with information from the CMD token.
// /// @param tokens
// /// @return 0
// int	cmd_maker(t_token *tokens)
// {
// 	t_command	*tab;

// 	tab = (t_command *)ft_calloc(1, sizeof(t_command));
// 	if (!tab)
// 		return (-1);
// 	tab->cmd = ft_split_minishell(tokens->cmd, ' ');
// 	rem_quotes(tab->cmd);
// 	if (tab->cmd == NULL)
// 		return (1);
// 	tab->cmd_name = ft_strdup(tab->cmd[0]);
// 	tab->in_fd = STDIN;
// 	tab->out_fd = STDOUT;
// 	tokens->table = tab;
// 	return (0);
// }

void	ft_count_pipes(t_lex *lexer_list, t_cmd_inf *tools)
{
	t_lex	*tmp;

	tmp = lexer_list;
	tools->pipe = 0;
	while (tmp)
	{
		if (tmp->token == PIPE)
			tools->pipe++;
		tmp = tmp->next;
	}
}

t_cmd	*create_cmd_structure(int cmd_size, int arg_size)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
	{
		perror("Memory allocation error");
	}
	cmd->final_cmd = malloc(sizeof(char *) * cmd_size);
	cmd->final_arg = malloc(sizeof(char *) * arg_size);
	cmd->input = malloc(sizeof(char *) * arg_size);
	cmd->output = malloc(sizeof(char *) * arg_size);
	if (!cmd->final_cmd || !cmd->final_arg)
	{
		perror("Memory allocation error");
	}
	cmd->input = NULL;
	cmd->output = NULL;
	return (cmd);
}

// while (list != NULL)
// {
// 	if (list->str != NULL)
// 	{
// 		cmd->final_cmd[i] = ft_strdup(list->str);
// 		printf("new cmd%s\n",cmd->final_cmd[i]);
// 		list = list->next;
// 		i++;

// 		while (list != NULL && list->str != NULL)
// 		{
// 			cmd->final_arg[j] = ft_strdup(list->str);
// 			printf("new arg%s\n",cmd->final_arg[j]);
// 			j++;
// 			list = list->next;
// 		}
// 	}
// 	else
// 	{
// 		list = list->next;
// 	}
// }

void	free_cmd_structure(t_cmd *cmd, int cmd_size, int arg_size)
{
	for (int k = 0; k < cmd_size; k++)
	{
		free(cmd->final_cmd[k]);
	}
	free(cmd->final_cmd);
	for (int k = 0; k < arg_size; k++)
	{
		free(cmd->final_arg[k]);
	}
	free(cmd->final_arg);
	free(cmd);
}

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

void    ft_parsing(t_lex *list, t_cmd *cmd, char **envp)
{
    int   i;
    int   j;
    int   k;
    char  *cmd_str;

    i = -1;
    j = 0;
    k = 0;
    while (list)
    {
        if (!list->str)
        {
            if (ft_check_red(list->token) == 4)
            {
                cmd->input = list->str;
            }
            else if (ft_check_red(list->token) == 2)
            {
                cmd->output = list->str;
            }
            list = list->next;
        }
        else
        {
            cmd_str = NULL;
            while (list && list->str)
            {
                if (cmd_str)
                {
                    cmd_str = ft_strjoin(cmd_str, " ");
                }
                cmd_str = ft_strjoin(cmd_str, list->str);
                cmd->final_arg[j] = list->str;
                list = list->next;
                j++;
            }
            cmd->final_cmd[++i] = cmd_str;
            // printf("----------> %s\n", cmd->final_cmd[k]);
            k++;
        }
    }
}

void	print_list(t_lex *list)
{
	while (list != NULL)
	{
		printf("printf list here: %s\n", list->str);
		list = list->next;
	}
}
void	print_token(t_lex *list)
{
	while (list != NULL)
	{
		printf("printf Token here: %i\n", list->token);
		list = list->next;
	}
}
int	ft_red(void)
{
	return (0);
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
			// free
			exit(0);
		}

		token = create_cmd_structure(20, 20);
		c.command = ft_strtrim(cmd, " ");
		printf("result 1  %s\n", c.command);
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
			else if (ft_strncmp(token->final_cmd[0], "history", 7) == 0)
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
	return (0);
}
