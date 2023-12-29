/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelhaj- <mbelhaj-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 03:26:48 by mbelhaj-          #+#    #+#             */
/*   Updated: 2023/04/01 03:54:11 by mbelhaj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*rlt;
	char	*p;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	rlt = malloc(len1 + len2 + 1);
	p = rlt;
	if (rlt == NULL)
		return (NULL);
	while (*s1 != '\0')
	{
		*p++ = *s1++;
	}
	while (*s2 != '\0')
	{
		*p++ = *s2++;
	}
	*p = '\0';
	return (rlt);
}
