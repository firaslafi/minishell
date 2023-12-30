/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_lex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelhaj- <mbelhaj-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 02:40:59 by mbelhaj-          #+#    #+#             */
/*   Updated: 2023/12/30 13:02:12 by mbelhaj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lex	*ft_lex_new(char *str, int token)
{
	t_lex		*new_element;
	static int	i;

	i = 0;
	new_element = (t_lex *)malloc(sizeof(t_lex));
	if (!new_element)
		return (0);
	new_element->str = str;
	new_element->token = token;
	new_element->i = i++;
	new_element->next = NULL;
	new_element->prev = NULL;
	return (new_element);
}

void	ft_lex_add(t_lex **lst, t_lex *new)
{
	t_lex	*tmp;

	tmp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

int	ft_add_node(char *str, t_token token, t_lex **list)
{
	t_lex	*node;

	node = ft_lex_new(str, token);
	if (!node)
		return (0);
	ft_lex_add(list, node);

	return (1);
}
