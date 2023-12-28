/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelhaj- <mbelhaj-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 22:44:04 by mbelhaj-          #+#    #+#             */
/*   Updated: 2023/12/16 02:28:32 by mbelhaj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_find_double(char *c, int index, int *q)
{
	int	i;

	i = index + 1;
	*q += 1;
	while (c[i] && c[i] != 34)
		i++;
	if (c[i] == 34)
		*q += 1;
	return (i - index);
}

int	ft_find_single(char *c, int index, int *q)
{
	int	i;

	i = index + 1;
	*q += 1;
	while (c[i] && c[i] != 39)
		i++;
	if (c[i] == 39)
		*q += 1;
	return (i - index);
}

int	ft_single_quote(char *c)
{
	int	index;
	int	single;

	index = 0;
	single = 0;
	while (c[index])
	{
		if (c[index] == 39)
			index += ft_find_single(c, index, &single);
		index++;
	}
	if (single > 0 && single % 2 != 0)
		return (0);
	return (1);
}

int	ft_double_qoute(char *c)
{
	int	index;
	int	doubl;

	index = 0;
	doubl = 0;
	while (c[index])
	{
		if (c[index] == 34)
			index += ft_find_double(c, index, &doubl);
		index++;
	}
	if (doubl > 0 && doubl % 2 != 0)
		return (0);
	return (1);
}

int	ft_quotes_both(char *str, int i)
{
	int		j;
	char	quote;

	j = 0;
	if (str[i + j] == 34 || str[i + j] == 39)
	{
		quote = str[i + j];
		j++;
		while (str[i + j] != quote && str[i + j])
		{
			j++;
		}
		j++;
	}
	return (j);
}
