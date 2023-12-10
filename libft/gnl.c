/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelhaj- <mbelhaj-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 15:58:45 by mbelhaj-          #+#    #+#             */
/*   Updated: 2023/08/12 14:31:47 by mbelhaj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_line(char *save)
{
	char	*s;
	t_gnl	gnl;

	gnl.i = 0;
	if (!save[gnl.i])
		return (NULL);
	while (save[gnl.i] && save[gnl.i] != '\n')
		gnl.i++;
	s = (char *)malloc(sizeof(char) * (gnl.i + 2));
	if (!s)
		return (NULL);
	gnl.i = 0;
	while (save[gnl.i] && save[gnl.i] != '\n')
	{
		s[gnl.i] = save[gnl.i];
		gnl.i++;
	}
	if (save[gnl.i] == '\n')
	{
		s[gnl.i] = save[gnl.i];
		gnl.i++;
	}
	s[gnl.i] = '\0';
	return (s);
}

char	*ft_save_data(char *save)
{
	char	*s;
	t_gnl	gnl;

	gnl.i = 0;
	while (save[gnl.i] && save[gnl.i] != '\n')
		gnl.i++;
	if (!save[gnl.i])
	{
		free(save);
		return (NULL);
	}
	s = (char *)malloc(sizeof(char) * (ft_strlen(save) - gnl.i + 1));
	gnl.i++;
	gnl.y = 0;
	if (!s)
	{		
		free(s);
		return (NULL);
	}
	while (save[gnl.i])
		s[gnl.y++] = save[gnl.i++];
	s[gnl.y] = '\0';
	free(save);
	return (s);
}

char	*ft_read(int fd, char *save)
{
	char	*buff;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	save = ft_read_data (fd, save, buff);
	return (save);
}

char	*ft_read_data(int fd, char *save, char *buff)
{
	int		read_bytes;

	read_bytes = 1;
	while (!ft_strchr_gnl(save, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(save);
			free(buff);
			return (NULL);
		}
		buff[read_bytes] = '\0';
		save = ft_strjoin_gnl(save, buff);
	}
	free (buff);
	return (save);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	save = ft_read(fd, save);
	if (!save)
		return (NULL);
	line = ft_line(save);
	save = ft_save_data(save);
	return (line);
}
