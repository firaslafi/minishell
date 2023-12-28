/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelhaj- <mbelhaj-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:13:53 by mbelhaj-          #+#    #+#             */
/*   Updated: 2023/03/28 05:00:03 by mbelhaj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_memcmp(const void *ptr1, const void *ptr2, int n)
{
	const unsigned char	*p1;
	const unsigned char	*p2;

	p1 = (const unsigned char *) ptr1;
	p2 = (const unsigned char *) ptr2;
	while (n-- > 0)
	{
		if (*p1 != *p2)
		{
			return ((unsigned char)*p1 - (unsigned char)*p2);
		}
		p1++;
		p2++;
	}
	return (0);
}
