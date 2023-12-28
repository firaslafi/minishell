/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelhaj- <mbelhaj-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:23:36 by mbelhaj-          #+#    #+#             */
/*   Updated: 2023/12/20 14:23:59 by mbelhaj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_parse *ft_new_cmd(char **str, int num_redirections, t_lex *redirections)
{
    t_parse *new_element;

    // Allocate memory for the new t_parse structure
    new_element = (t_parse *)malloc(sizeof(t_parse));
    if (!new_element)
        return (0); // Return NULL if memory allocation fails

    // Initialize the fields of the new structure
    new_element->str = str;
    // new_element->builtin = builtin_arr(str[0]);
    new_element->hd_file_name = NULL;
    new_element->num_redirections = num_redirections;
    new_element->redirections = redirections;
    new_element->next = NULL;
    new_element->prev = NULL;

    return (new_element); // Return the pointer to the new structure
}


void ft_new_cmd_add(t_parse **lst, t_parse *new)
{
    t_parse *tmp;

    tmp = *lst;

    // If the list is empty, set the new structure as the head
    if (*lst == NULL)
    {
        *lst = new;
        return;
    }

    // Iterate to the end of the list
    while (tmp->next != NULL)
        tmp = tmp->next;

    // Add the new structure to the end of the list
    tmp->next = new;
    new->prev = tmp;
}


void ft_cmd_clear(t_parse **lst)
{
	t_parse *tmp;
    t_lex *re_tmp;

    // If the list is empty, return
    if (!*lst)
        return;

    // Iterate through the list
    while (*lst)
    {
        // Save the next node and redirections pointer
        tmp = (*lst)->next;
        re_tmp = (*lst)->redirections;

        // Clear the redirections linked list
        ft_clear_lex(&re_tmp);

        // Free the memory associated with the 'str' array
        if ((*lst)->str)
            ft_free_arr((*lst)->str);

        // Free the memory associated with 'hd_file_name'
        if ((*lst)->hd_file_name)
            free((*lst)->hd_file_name);

        // Free the memory associated with the current node
        free(*lst);

        // Move to the next node
        *lst = tmp;
    }

    // Set the list pointer to NULL after clearing
    *lst = NULL;
}