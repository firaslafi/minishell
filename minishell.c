/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelhaj- <mbelhaj-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:19:21 by flafi             #+#    #+#             */
/*   Updated: 2023/12/14 23:35:09 by mbelhaj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

// t_mshell	*ft_init(char **env)
// {
// 	t_mshell	*mini;

// 	return (mini);
// }


int ft_get_token(t_cmd_inf cmd)
{
	int i;
	int j;

	i = 0;
	while (cmd.command[i])
	{
		j = 0;
		i += ft_remove_space(cmd.command);
	}
	
	return(0);
}

char	*ft_cmd(void)
{
	char	*cmd;

	rl_bind_key('\t', rl_insert);
	cmd = readline("minishell >");
	if (!cmd)
		printf("\nExiting...\n");
	if (cmd[0] != '\0')
		add_history(cmd);
	return (cmd);
}

void	minishell_loop(t_mshell *mini)
{
	char		*cmd;
	t_cmd_inf	c;

	mini = NULL;
	while (1)
	{
		cmd = ft_cmd();
		if (!cmd)
		{
			// free
			exit(0);
		}
		c.command = ft_strtrim(cmd, " ");
		printf ("result 1  %s\n", c.command);
		if (!ft_double_qoute(c.command))
			printf("no double quote \n");
		if (!ft_single_quote(c.command))
			printf("no signle quote \n");
		
	}
}

int	main(int argc, char **argv)
{
	t_mshell	*mini;

	// char		*input;
	mini = NULL;
	// mini = ft_init(env);
	if (argv[1] || argc != 1)
	{
		printf("ERROR");
		exit(0);
	}
	minishell_loop(mini);
	return (0);
}
