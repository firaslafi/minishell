/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelhaj- <mbelhaj-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 01:20:45 by flafi             #+#    #+#             */
/*   Updated: 2023/12/30 13:01:18 by mbelhaj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_historylist	*ft_hstlast(t_historylist *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_addhst_back(t_historylist **history, t_historylist *new)
{
	t_historylist	*last;

	if (history)
	{
		if (*history)
		{
			last = ft_hstlast(*history);
			last->next = new;
		}
		else
			*history = new;
	}
}

// Add the entry to the front of the list
void	add_history_front(t_historylist **history, t_historylist *newEntry)
{
	ft_addhst_back(history, newEntry);
}

// Create a new history entry & add to the front of the list
// do a rework for strdup or add to the lst free
void	ft_add_history(const char *command, t_historylist **history,
		t_mem_block **lst)
{
	t_historylist *newEntry;

	newEntry = ft_malloc(lst, sizeof(t_historylist));
	newEntry->command = ft_strdup_s(command, lst);
	newEntry->next = NULL;
	add_history_front(history, newEntry);
}
