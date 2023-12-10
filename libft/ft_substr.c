/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelhaj- <mbelhaj-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 01:06:55 by mbelhaj-          #+#    #+#             */
/*   Updated: 2023/04/12 19:00:50 by mbelhaj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t n)
{
	char		*str;
	const char	*p;
	size_t		i;
	size_t		s_len;

	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (s_len - start < n)
		n = s_len - start;
	str = malloc((n + 1) * sizeof(char));
	p = s + start;
	i = 0;
	if (str == NULL)
		return (NULL);
	while (*p != '\0' && i < n)
	{
		str[i] = *p;
		p++;
		i++;
	}
	str[i] = '\0';
	return (str);
}
