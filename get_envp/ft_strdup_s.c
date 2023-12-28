/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 01:19:23 by flafi             #+#    #+#             */
/*   Updated: 2023/12/28 01:19:25 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_calloc_s(size_t nelem, size_t elemsize, t_mem_block **lst)
{
	void	*ptr;

	ptr = ft_malloc(lst, nelem * elemsize);
	if (ptr)
		ft_bzero(ptr, (nelem * elemsize));
	return (ptr);
}

char	*ft_strdup_s(const char *s, t_mem_block **lst)
{
	void			*ptr;
	unsigned char	chr;
	int				i;
	int				len;

	len = ft_strlen(s) + 1;
	ptr = ft_calloc_s(len, 1, lst);


	if (!ptr)
		return (free(ptr), NULL);
	i = 0;
	while (len--)
	{
		chr = (unsigned char) s[i];
		((unsigned char *) ptr)[i] = chr;
		i++;
	}
	return ((char *) ptr);
}
