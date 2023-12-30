/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelhaj- <mbelhaj-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 03:55:42 by mbelhaj-          #+#    #+#             */
/*   Updated: 2023/04/06 15:23:44 by mbelhaj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		len1;
	char const	*start;
	char const	*end;
	char		*rlt;
	size_t		new_len;

	start = s1;
	len1 = ft_strlen(s1);
	end = s1 + len1 - 1;
	while (*start && ft_strchr(set, *start))
		start++;
	while (end > start && ft_strchr(set, *end))
		end--;
	new_len = (end - start) + 1;
	rlt = malloc(new_len + 1);
	if (rlt == NULL)
		return (NULL);
	ft_memcpy(rlt, start, new_len);
	rlt[new_len] = '\0';
	return (rlt);
}
