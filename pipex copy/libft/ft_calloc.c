/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelhaj- <mbelhaj-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 23:03:40 by mbelhaj-          #+#    #+#             */
/*   Updated: 2023/03/31 02:31:15 by mbelhaj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t nelem, size_t n_size)
{
	void	*ptr;

	ptr = malloc(nelem * n_size);
	if (!ptr)
	{
		return (ptr);
	}
	ft_bzero(ptr, nelem * n_size);
	return (ptr);
}
