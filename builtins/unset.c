/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 02:38:03 by flafi             #+#    #+#             */
/*   Updated: 2023/12/30 22:21:13 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// if its the head
// Find the previous node
// If the node to be removed is in the middle or end of the list

void	var_search_remove(char *str, t_cmd_inf minish)
{
	t_list	*current;
	t_list	*previous_node;

	current = minish.envlst;
	while (current != NULL)
	{
		if (ft_strncmp(str, current->content, ft_strlen(str)) == 0)
		{
			if (minish.envlst == current)
			{
				minish.envlst = current->next;
				free(current);
			}
			previous_node = minish.envlst;
			while (previous_node != NULL && previous_node->next != current)
				previous_node = previous_node->next;
			if (previous_node != NULL)
			{
				previous_node->next = current->next;
				free(current);
			}
		}
		current = current->next;
	}
}

int	ft_unset(char **cmd, t_cmd_inf minish)
{
	int	i;

	(void)minish;
	i = 0;
	if (!cmd[1])
		return (1);
	while (cmd[i])
	{
		var_search_remove(cmd[i], minish);
		i++;
	}
	return (0);
}

// env for env lol
int	ft_env(t_cmd_inf minish)
{
	t_list	*current;

	current = minish.envlst;
	while (current != NULL)
	{
		ft_putendl_fd(current->content, 1);
		current = current->next;
	}
	minish.rtn_code = 0;
	return (0);
}
