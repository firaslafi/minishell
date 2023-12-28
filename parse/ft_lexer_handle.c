/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_handle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelhaj- <mbelhaj-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:18:32 by mbelhaj-          #+#    #+#             */
/*   Updated: 2023/12/20 14:22:20 by mbelhaj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lex	*ft_clear_one(t_lex **lst)
{
	if ((*lst)->str)
	{
		free((*lst)->str);
		(*lst)->str = NULL;
	}
	free(*lst);
	*lst = NULL;
	return (NULL);
}

void	ft_delete_first(t_lex **lst)
{
	t_lex	*node;

	node = *lst;
	*lst = node->next;
	if ((*lst)->str)
	{
		free((*lst)->str);
		(*lst)->str = NULL;
	}
	free(*lst);
	*lst = NULL;
	if (*lst)
		(*lst)->prev = NULL;
}

void	ft_delete_one(t_lex **lst, int key)
{
	t_lex	*node;
	t_lex	*prev;
	t_lex	*start;

	start = *lst;
	node = start;
	if ((*lst)->i == key)
	{
		ft_delete_first(lst);
		return ;
	}
	while (node && node->i != key)
	{
		prev = node;
		node = node->next;
	}
	if (node)
		prev->next = node->next;
	else
		prev->next = NULL;
	if (prev->next)
		prev->next->prev = prev;
	ft_clear_one(&node);
	*lst = start;
}

// Check if the list is not empty
// Save the next node
// Free the memory for the string
// Free the memory for the lexer node
// Move to the next node
// Set the head of the list to NULL

void	ft_clear_lex(t_lex **lex)
{
	t_lex	*tmp;

	if (!*lex)
		return ;
	while (*lex)
	{
		tmp = (*lex)->next;
		if ((*lex)->str)
			free((*lex)->str);
		free(*lex);
		*lex = tmp;
	}
	*lex = NULL;
}