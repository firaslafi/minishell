/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 23:49:26 by flafi             #+#    #+#             */
/*   Updated: 2023/12/31 02:36:20 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

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
			printf("%s \n", lol);
			free(lol);
			return (0);
		}
		current = current->next;
	}
	return (1);
}
