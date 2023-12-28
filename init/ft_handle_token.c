/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelhaj- <mbelhaj-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 02:46:52 by mbelhaj-          #+#    #+#             */
/*   Updated: 2023/12/24 19:15:18 by mbelhaj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_save_token(char *str, int i, t_lex **lex)
{
	int	token;
	int	next_token;

	token = ft_check(str[i]);
	next_token = ft_check(str[i + 1]);
	if (token == GREAT && next_token == GREAT)
	{
		if (!ft_add_node(NULL, GREAT_GREAT, lex))
			return (-1);
		return (2);
	}
	else if (token == LESS && next_token == LESS)
	{
		if (!ft_add_node(NULL, LESS_LESS, lex))
			return (-1);
		return (2);
	}
	else if (token && !next_token)
	{
		if (!ft_add_node(NULL, token, lex))
			return (-1);
		return (1);
	}
	else 
		return(-1);
	return (0);
}

int	ft_save_other(char *str, int i, t_lex **lex)
{
	int		j;
	char	*new;

	j = 0;
	while (str[i + j] && !(ft_check(str[i + j])))
	{
		j += ft_quotes_both(str, (i + j));
		if (str[i + j] == ' ')
			break ;
		else
			j++;
	}
	new = ft_substr(str, i, j);
	if (!ft_add_node(new, 0, lex))
		return (-1);
	return (j);
}

int	is_whitespace(char c)
{
	return (c == ' ' || (c > 8 && c < 14));
}

int	skip_spaces(char *str, int i)
{
	int	j;

	j = 0;
	while (is_whitespace(str[i + j]))
		j++;
	return (j);
}

int	ft_get_token(t_cmd_inf *cmd)
{
	int	i;
	int	index;

	cmd->list = NULL;
	i = 0;
	while (cmd->command[i])
	{
		index = 0;
		i += skip_spaces(cmd->command, i);
		if (ft_check(cmd->command[i]))
		{
			index = ft_save_token(cmd->command, i, &cmd->list);
		}
		else
		{
			index = ft_save_other(cmd->command, i, &cmd->list);
		}
		// printf("index %i\n", index);
		if (index < 0)
			return (0);
		i += index;
	}
	return (1);
}
