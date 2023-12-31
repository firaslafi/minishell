/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 19:01:29 by flafi             #+#    #+#             */
/*   Updated: 2023/12/02 19:04:04 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

static t_mem_block	*ft_new_mem_block(void *pointer)
{
	t_mem_block	*block;

	block = malloc(sizeof(t_mem_block));
	if (!block)
		return (NULL);
	block->block_pointer = pointer;
	block->next = NULL;
	return (block);
}

static void	ft_add_mem_block(t_mem_block **lst, void *pointer)
{
	t_mem_block	*temp;

	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = ft_new_mem_block(pointer);
	}
	else
	{
		temp = *lst;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = ft_new_mem_block(pointer);
	}
}

void	*ft_malloc(t_mem_block **lst, int size)
{
	void	*p;

	if (size <= 0)
		return (NULL);
	p = malloc(size);
	if (!p)
		return (NULL);
	ft_add_mem_block(lst, p);
	return (p);
}

void	ft_free_all(t_mem_block **lst)
{
	t_mem_block	*temp;
	t_mem_block	*to_free;

	if (!lst || !*lst)
		return ;
	temp = *lst;
	while (temp != NULL)
	{
		to_free = temp;
		temp = temp->next;
		free(to_free->block_pointer);
		free(to_free);
	}
	*lst = NULL;
}
