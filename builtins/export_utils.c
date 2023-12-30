/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelhaj- <mbelhaj-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 12:55:39 by mbelhaj-          #+#    #+#             */
/*   Updated: 2023/12/30 12:55:58 by mbelhaj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_export_print(t_cmd_inf minish)
{
	t_list	*current;

	current = minish.envlst;
	while (current != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(current->content, 1);
		current = current->next;
	}
}

// looks for the = and quotes and return the pos first chr of the value
// 39 is the ascii of '
// if (pos != -1 && (str[pos + 1] == '\"' || str[pos + 1] == '\''))
//     pos = pos ;
int	find_value(char *str)
{
	int	i;
	int	len;
	int	pos;

	i = 0;
	len = ft_strlen(str);
	pos = -1;
	while (i < len)
	{
		if (str[i] == '=')
		{
			pos = i;
			break ;
		}
		i++;
	}
	return (pos);
}

// first char should not be number and should be alpha numeritic min 1 chr
int	check_alphanum(char *str)
{
	if (ft_isdigit(str[0]) == 1)
		return (0);
	if (ft_isalpha(str[0]) == 1)
		return (1);
	if (str[1] != '\0' && ft_isalpha(str[1]) == 1)
		return (1);
	else
		return (0);
}

char	*remove_qt(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\"' && str[i] != '\'')
		{
			str[j] = str[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	return (str);
}
