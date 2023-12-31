/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:19:21 by flafi             #+#    #+#             */
/*   Updated: 2023/12/31 03:30:16 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"
#include <time.h>

int	ft_get_input(t_lex *list, t_cmd *cmd, t_mem_block *lst)
{
	int	i;
	int	j;

	lst = NULL;
	i = -1;
	j = 0;
	while (list != NULL)
	{
		if (list->str == NULL)
			list = ft_all_token(list, cmd, lst);
		else
		{
			cmd->final_cmd[++i] = ft_strdup_s(list->str, &lst);
			list = list->next;
			while (list != NULL && list->str != NULL)
			{
				cmd->final_arg[j] = ft_strdup_s(list->str, &lst);
				cmd->final_cmd[i] = ft_strjoin(cmd->final_cmd[i], " ");
				cmd->final_cmd[i] = ft_strjoin(cmd->final_cmd[i],
						cmd->final_arg[j++]);
				list = list->next;
			}
		}
	}
	return (i + 1);
}

int	ft_dollar_sign(t_cmd *cmd, t_cmd_inf c)
{
	int	k;

	k = 0;
	while (cmd->final_cmd[k])
	{
		if (ft_strncmp(&cmd->final_cmd[k][0], "$", 1) == 0)
		{
			if (ft_strncmp(&cmd->final_cmd[k][1], "$", 1) == 0)
			{
				printf("%i", my_getpid());
				return (1);
			}
			else
			{
				check_exist_envp(cmd->final_cmd[k], c);
				return (1);
			}
		}
		k++;
	}
	return (0);
}

void	ft_parsing(t_lex *list, t_cmd *cmd, char **envp, t_cmd_inf c)
{
	t_mem_block	*lst;

	lst = NULL;
	cmd->num_cmd = ft_get_input(list, cmd, lst);
	// if (cmd->final_cmd != NULL && *cmd->final_cmd != NULL)
		// if (ft_dollar_sign(cmd, c))
		// 	ft_free(cmd->final_cmd);
	if (cmd->final_cmd != NULL && *cmd->final_cmd != NULL)
	{
		if (!ft_run_builtin(cmd))
			is_builtin(cmd->final_cmd, c);
		else if (ft_strncmp(cmd->final_cmd[0], "history", 7) == 0)
			printf_hst(c.history);
		else
			pipex(cmd, envp, cmd->num_cmd);
	}
	else
		free(cmd);
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
		if (!ft_double_qoute(c.command))
			printf("no double quote \n");
		if (!ft_single_quote(c.command))
			printf("no signle quote \n");
		if (!ft_get_token(&c))
			printf("\nOKAY\n");
		ft_parsing(c.list, token, envp, c);
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
