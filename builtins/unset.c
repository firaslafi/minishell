/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 02:38:03 by flafi             #+#    #+#             */
/*   Updated: 2023/12/28 02:38:16 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// need hearder her too

#include "../minishell.h"

// void remove_node(t_mini minish)
// {
    
// }
int var_search_remove(char *str, t_cmd_inf minish)
{
    t_list *current;
    t_list *previous_node;
    
    current = minish.envlst;
    while (current != NULL) 
    {
        if(ft_strncmp(str, current->content, ft_strlen(str)) == 0)
            {
                 // if its the head
                if (minish.envlst == current) 
                {
                    minish.envlst= current->next;
                    free(current);
                    return (0);
                }
                // Find the previous node
                previous_node = minish.envlst;
                while (previous_node != NULL && previous_node->next != current)
                    previous_node = previous_node->next;

                // If the node to be removed is in the middle or end of the list
                if (previous_node != NULL) 
                {
                    previous_node->next = current->next;
                    free(current);
                }
                return (0);
            }
        current = current->next;
    }
    return (1);
}

void ft_unset(char **cmd, t_cmd_inf minish)
{
    int i;
    // char *var_name;
    (void)minish;
    i = 0;   
    if (!cmd[1])
        return;
    while (cmd[i])
    {
        var_search_remove(cmd[i], minish);
  
        i++;
    }
    
}