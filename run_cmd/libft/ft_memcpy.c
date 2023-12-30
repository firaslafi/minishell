/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelhaj- <mbelhaj-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:33:22 by mbelhaj-          #+#    #+#             */
/*   Updated: 2023/04/06 15:05:03 by mbelhaj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

char	*ft_memcpy(void *dest, const void *src, int n)
{
	int		i;
	char	*d;
	char	*s;

	d = (char *) dest;
	s = (char *) src;
	if (!dest && !src)
		return (dest);
	i = 0;
	while (n--)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
//norminette is okay