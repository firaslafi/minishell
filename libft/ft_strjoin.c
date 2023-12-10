/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelhaj- <mbelhaj-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 03:26:48 by mbelhaj-          #+#    #+#             */
/*   Updated: 2023/08/12 14:30:45 by mbelhaj-         ###   ########.fr       */
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

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str;
	t_gnl	gnl;

	if (!s1)
		s1 = ft_just_malloc(s1);
	gnl.len1 = ft_strlen(s1);
	gnl.len2 = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (gnl.len1 + gnl.len2 + 1));
	if (!str)
		return (NULL);
	gnl.y = 0;
	while (gnl.y < gnl.len1)
	{
		str[gnl.y] = s1[gnl.y];
		gnl.y++;
	}
	while (gnl.y < gnl.len1 + gnl.len2)
	{
		str[gnl.y] = s2[gnl.y - gnl.len1];
		gnl.y++;
	}
	str[gnl.y] = '\0';
	free(s1);
	return (str);
}

char	*ft_just_malloc(char *s1)
{
	s1 = (char *)malloc(1 * sizeof(char));
	s1[0] = '\0';
	return (s1);
}
