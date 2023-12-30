/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelhaj- <mbelhaj-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:19:21 by flafi             #+#    #+#             */
/*   Updated: 2023/12/30 14:41:54 by mbelhaj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"
#include <time.h>

t_cmd	*create_cmd_structure(int cmd_size, int arg_size, t_mem_block *lst)
{
	t_cmd	*cmd;

	cmd = ft_malloc(&lst, sizeof(t_cmd));
	if (!cmd)
	{
		perror("Memory allocation error");
	}
	cmd->final_cmd = ft_malloc(&lst, sizeof(char *) * cmd_size);
	cmd->final_arg = ft_malloc(&lst, sizeof(char *) * arg_size);
	cmd->input = ft_malloc(&lst, sizeof(char *) * arg_size);
	cmd->output = ft_malloc(&lst, sizeof(char *) * arg_size);
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

pid_t	my_getpid(void)
{
	srand((unsigned int)time(NULL));
	return (rand() % 10000 + 1000);
}

int	check_exist_envp(char *var_name, t_cmd_inf minish)
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

// void	ft_get_input(t_lex *list, t_cmd *cmd, t_mem_block *lst)
// {
// 	if (list->token == 2)
// 	{
// 		list = list->next;
// 		cmd->output = ft_strdup_s(list->str, &lst);
// 		cmd->flags = ft_strjoin(cmd->flags, "G");
// 		list = list->next;
// 	}
// 	else if (list->token == 3)
// 	{
// 		list = list->next;
// 		cmd->output = ft_strdup_s(list->str, &lst);
// 		cmd->flags = ft_strjoin(cmd->flags, "G_G");
// 		list = list->next;
// 	}
// 	else if (list->token == 4)
// 	{
// 		list = list->next;
// 		cmd->input = ft_strdup_s(list->str, &lst);
// 		cmd->flags = ft_strjoin(cmd->flags, "L");
// 		list = list->next;
// 	}
// 	else if (list->token == 5)
// 	{
// 		list = list->next;
// 		cmd->here_doc = ft_strdup_s(list->str, &lst);
// 		cmd->flags = ft_strjoin(cmd->flags, "L_L");
// 		list = list->next;
// 	}
// 	else
// 		list = list->next;
// }

void	ft_parsing(t_lex *list, t_cmd *cmd, char **envp, t_cmd_inf c)
{
	int			i;
	int			j;
	int			k;
	t_mem_block	*lst;

	lst = NULL;
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
				cmd->flags = ft_strjoin(cmd->flags, "G");
				list = list->next;
			}
			else if (list->token == 3)
			{
				list = list->next;
				cmd->output = ft_strdup_s(list->str, &lst);
				cmd->flags = ft_strjoin(cmd->flags, "G_G");
				list = list->next;
			}
			else if (list->token == 4)
			{
				list = list->next;
				cmd->input = ft_strdup_s(list->str, &lst);
				cmd->flags = ft_strjoin(cmd->flags, "L");
				list = list->next;
			}
			else if (list->token == 5)
			{
				list = list->next;
				cmd->here_doc = ft_strdup_s(list->str, &lst);
				cmd->flags = ft_strjoin(cmd->flags, "L_L");
				list = list->next;
			}
			else
				list = list->next;
		}
		else
		{
			i++;
			cmd->final_cmd[i] = ft_strdup_s(list->str, &lst);
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
	while (cmd->final_cmd[k])
	{
		j = 0;
		if (ft_strncmp(&cmd->final_cmd[k][0], "$", 1) == 0)
		{
			if (ft_strncmp(&cmd->final_cmd[k][1], "$", 1) == 0)
				printf("%i", my_getpid());
			else
				check_exist_envp(cmd->final_cmd[k], c);
			j++;
		}
		k++;
	}
	if (cmd->final_cmd != NULL && *cmd->final_cmd != NULL)
	{
		if (!ft_run_builtin(cmd))
			is_builtin(cmd->final_cmd, c);
		else if (ft_strncmp(cmd->final_cmd[0], "history", 7) == 0)
			printf_hst(c.history);
		else
			pipex(cmd, envp, (i + 1));
	}
	else
		free(cmd);
	// free(cmd); // Free memory for an empty token
	// printf("flags ----------->> %s\n",cmd->flags);
	// execute_command(cmd,envp);
	//  ft_free_all(&lst);
	//  ft_rest();
	// 	free_cmd_structure(cmd, k, j);
}

void	minishell_loop(t_cmd_inf c, char **envp)
{
	char		*cmd;
	t_cmd		*token;
	int			i;
	t_mem_block	*lst;

	i = 0;
	while (1)
	{
		cmd = ft_cmd(&c);
		if (!cmd)
		{
			free(cmd);
			exit(0);
		}
		lst = NULL;
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
		ft_parsing(c.list, token, envp, c);
		// // ft_free_all(c.lst);
		// ft_free_all(&lst);
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
