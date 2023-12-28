/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelhaj- <mbelhaj-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 07:32:14 by mbelhaj-          #+#    #+#             */
/*   Updated: 2023/04/12 23:54:38 by mbelhaj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s == c)
		{
			if (in_word)
				in_word = 0;
		}
		else
		{
			if (!in_word)
			{
				count++;
				in_word = 1;
			}
		}
		s++;
	}
	return (count);
}

static int	word_len(const char *s, char c)
{
	int	len;

	len = 0;
	while (*s && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

static void	*ft_free(char **arr, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(arr[j]);
		j++;
	}
	free((arr));
	return (NULL);
}

static void	ft_move(char *word, const char *s, char c)
{
	int		j;

	j = 0;
	while (j < word_len(s, c))
	{
		word[j] = s[j];
		j++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		i;
	char	*word;

	arr = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s == c && s++)
			continue ;
		word = malloc((word_len(s, c) + 1) * sizeof(char));
		if (word == NULL)
			return (ft_free(arr, i));
		ft_move(word, s, c);
		word[word_len(s, c)] = '\0';
		arr[i] = word;
		i++;
		s += word_len(s, c);
	}
	arr[i] = NULL;
	return (arr);
}
