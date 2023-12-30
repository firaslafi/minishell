/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_related.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 23:43:56 by flafi             #+#    #+#             */
/*   Updated: 2023/12/30 23:44:43 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

t_lex	*ft_token_2(t_lex *list, t_cmd *cmd, t_mem_block *lst)
{
	list = list->next;
	cmd->output = ft_strdup_s(list->str, &lst);
	cmd->flags = ft_strjoin(cmd->flags, "G");
	list = list->next;
	return (list);
}

t_lex	*ft_token_3(t_lex *list, t_cmd *cmd, t_mem_block *lst)
{
	list = list->next;
	cmd->output = ft_strdup_s(list->str, &lst);
	cmd->flags = ft_strjoin(cmd->flags, "G_G");
	list = list->next;
	return (list);
}

t_lex	*ft_token_4(t_lex *list, t_cmd *cmd, t_mem_block *lst)
{
	list = list->next;
	cmd->input = ft_strdup_s(list->str, &lst);
	cmd->flags = ft_strjoin(cmd->flags, "L");
	list = list->next;
	return (list);
}

t_lex	*ft_token_5(t_lex *list, t_cmd *cmd, t_mem_block *lst)
{
	list = list->next;
	cmd->here_doc = ft_strdup_s(list->str, &lst);
	cmd->flags = ft_strjoin(cmd->flags, "L_L");
	list = list->next;
	return (list);
}

t_lex	*ft_all_token(t_lex *list, t_cmd *cmd, t_mem_block *lst)
{
	if (list->token == 2)
		list = ft_token_2(list, cmd, lst);
	else if (list->token == 3)
		list = ft_token_3(list, cmd, lst);
	else if (list->token == 4)
		list = ft_token_4(list, cmd, lst);
	else if (list->token == 5)
		list = ft_token_5(list, cmd, lst);
	else
		list = list->next;
	return (list);
}
