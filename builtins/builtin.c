/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 02:30:15 by flafi             #+#    #+#             */
/*   Updated: 2023/12/31 04:31:16 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_exist_prnt(char *var_name, t_cmd_inf minish)
{
	t_list	*current;
	char	*lol;

	current = minish.envlst;
	var_name++;
	while (current)
	{
		if (ft_strncmp(var_name, current->content, ft_strlen(var_name)) == 0)
		{
			lol = ft_substr(current->content, ft_strlen(var_name) + 1,
					ft_strlen(current->content) - ft_strlen(var_name));
			return (lol);
		}
		current = current->next;
	}
	return (NULL);
}

void	ft_x(char **cmd, t_cmd_inf minish, int i)
{
	int	k;

	k = 0;
	if (ft_strncmp(&cmd[(i)][k], "$", 1) == 0)
	{
		if (ft_strncmp(&cmd[(i)][k + 1], "$", 1) != 0)
		{
			check_exist_envp(cmd[k], minish);
			return ;
		}
		else
		{
			check_exist_envp(cmd[k], minish);
			return ;
		}
		k++;
	}
	write(1, cmd[i], ft_strlen(cmd[i]));
	if (cmd[i + 1] != NULL)
		write(1, " ", 1);
}

void	ft_check_nflag(char **cmd, int *n_flag, int *i)
{
	if (cmd[1][0] == '-' && cmd[1][1] == 'n' && cmd[1][2] == '\0')
	{
		*n_flag = 1;
		*i = 2;
	}
}

int	printing(char *var_name, t_cmd_inf minish, char **cmd, int i)
{
	if (check_exist_prnt(var_name, minish) != NULL)
	{
		printf("%s", check_exist_prnt(var_name, minish));
		if (cmd[i + 1] != NULL)
			i++;
	}
	else
		printf("no not found!\n");
	return (i);
}

int	ft_echo(char **cmd, t_cmd_inf minish)
{
	int		n_flag;
	int		i;
	char	*var_name;

	i = 1;
	n_flag = 0;
	if (!cmd[1])
		return (write(1, "\n", 1), 1);
	ft_check_nflag(cmd, &n_flag, &i);
	while (cmd[i] != NULL)
	{
		remove_quotes(cmd[i]);
		if (ft_strncmp(&cmd[i][0], "$", 1) == 0)
		{
			var_name = cmd[i];
			i = printing(var_name, minish, cmd, i);
		}
		ft_x(cmd, minish, i);
		i++;
	}
	if (!n_flag)
		printf("\n");
	return (0);
}
