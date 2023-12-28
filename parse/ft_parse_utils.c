/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelhaj- <mbelhaj-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:24:18 by mbelhaj-          #+#    #+#             */
/*   Updated: 2023/12/20 14:34:43 by mbelhaj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Initialize a counter variable to zero
// Set 'tmp' to the head of the lexer list
// Iterate through the lexer list until a pipe token is encountered or the end is reached
// If the index (i) of the lexer element is non-negative,increment the counter
// Move to the next element in the lexer list
// Return the count of non-negative indices (arguments)

int	ft_count_args(t_lex *lex_list)
{
	t_lex	*tmp;
	int		i;

	i = 0;
	tmp = lex_list;
	while (tmp && tmp->token != PIPE)
	{
		if (tmp->i >= 0)
			i++;
		tmp = tmp->next;
	}
	return (i);
}



void	ft_count_p(t_lex *lex_list, t_cmd_inf *c)
{
	t_lex	*tmp;

	tmp = lex_list;
	c->pipe = 0;
	while (tmp)
	{
		if (tmp->token == PIPE)
			c->pipe++;
		tmp = tmp->next;
	}
}

t_parser_tools	ft_init_tools(t_cmd_inf *c)
{
	t_parser_tools	parser_tools;

	parser_tools.lexer_list = c->list;
	parser_tools.redirections = NULL;
	parser_tools.num_redirections = 0;
	parser_tools.tools = c;
	return (parser_tools);
}

// Frees the memory allocated for an array of strings
void ft_free_arr(char **arr)
{
    int i = 0;

    // Loop through each string in the array
    while (arr[i])
    {
        free(arr[i]); // Free the memory for each string
        i++;
    }

    free(arr); // Free the memory for the array itself
}
