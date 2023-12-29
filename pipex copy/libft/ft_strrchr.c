/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelhaj- <mbelhaj-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:26:14 by mbelhaj-          #+#    #+#             */
/*   Updated: 2023/04/07 17:28:01 by mbelhaj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

char	*ft_strrchr(const char *s, int c)
{
	const char	*l;

	l = NULL;
	while (*s != '\0')
	{
		if (*s == (char)c)
		{
			l = s;
		}
		s++;
	}
	if (*s == (char)c)
	{
		return ((char *)s);
	}
	return ((char *)l);
}
//norminette is okay