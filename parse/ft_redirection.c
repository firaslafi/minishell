/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelhaj- <mbelhaj-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:19:48 by mbelhaj-          #+#    #+#             */
/*   Updated: 2023/12/20 18:16:12 by mbelhaj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Recursively remove redirections from the lexer list
// Start with the head of the lexer list
// Continue until the end of the lexer list or a pipe token is encountered
// Stop if there's no more lexer or a pipe token is encountered
// Check for errors or add new redirections if needed
// Continue the process for the rest of the lexer list
void	ft_remove_re(t_parser_tools *parser_tools)
{
	t_lex	*lex;

	lex = parser_tools->lexer_list;
	while (lex && lex->token == 0)
		lex = lex->next;
	if (lex && lex->token == PIPE)
		return ;
	// if (!lex->next)
	// {
	// 	ft_clear_lex(&parser_tools->lexer_list);
	// 	ft_reset(parser_tools->tools);
	// }
	// if (lex->next->token)
	// {
	// 	ft_clear_lex(&parser_tools->lexer_list);
	// 	ft_reset(parser_tools->tools);
	// }
	if ((lex->token >= GREAT && lex->token <= LESS_LESS))
		ft_add_re(lex, parser_tools);
	ft_remove_re(parser_tools);
}

// Add a new redirection to the list and remove original lexer elements
// Create a new lexer element for redirection
// ERROR
// Remember the indices of the original lexer elements
int	ft_add_re(t_lex *lexer, t_parser_tools *parser_tools)
{
	t_lex	*node;
	int		index_1;
	int		index_2;

	node = ft_lex_new(ft_strdup(lexer->next->str), lexer->token);
	// if (!node)
	// {
	// 	ft_clear_lex(&parser_tools->lexer_list);
	// 	ft_reset(parser_tools->tools);
	// }
	ft_lex_add(&parser_tools->redirections, node);
	index_1 = lexer->i;
	index_2 = lexer->next->i;
	// Remove the original lexer elements representing redirection tokens
	ft_delete_one(&parser_tools->lexer_list, index_1);
	ft_delete_one(&parser_tools->lexer_list, index_2);
	// Increment the count of redirections
	parser_tools->num_redirections++;
	return (0); // Success
}
