/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelhaj- <mbelhaj-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 02:17:50 by mbelhaj-          #+#    #+#             */
/*   Updated: 2023/04/03 03:41:06 by mbelhaj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	len;
	char			*rlt;
	unsigned int	i;

	i = 0;
	len = 0;
	while (s[len])
		len++;
	rlt = (char *) malloc ((len + 1) * sizeof(char));
	if (!rlt)
		return (NULL);
	while (i < len)
	{
		rlt[i] = f(i, s[i]);
		i++;
	}
	rlt[len] = '\0';
	return (rlt);
}
