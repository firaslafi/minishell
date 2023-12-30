/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 23:03:26 by flafi             #+#    #+#             */
/*   Updated: 2023/12/30 23:30:46 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_find(char *pathcopy, char **pathsegments, char *pathToFind)
{
	char	*testpath;
	char	*fullpath;
	int		i;
	int		j;

	i = -1;
	while (pathsegments[++i] != NULL)
	{
		testpath = ft_strjoin(pathsegments[i], "/");
		fullpath = ft_strjoin(testpath, pathToFind);
		free(testpath);
		if (access(fullpath, X_OK) == 0)
		{
			free(pathcopy);
			j = 0;
			while (pathsegments[j] != NULL)
			{
				free(pathsegments[j]);
				j++;
			}
			return (free(pathsegments), fullpath);
		}
		free(fullpath);
	}
	return (NULL);
}

char	*ft_path(char *pathToFind, char **envp)
{
	char	*environmentpath;
	char	*pathcopy;
	char	**pathsegments;
	char	*fullpath;

	environmentpath = ft_getenv("PATH", envp);
	if (environmentpath == NULL)
		return (NULL);
	pathcopy = ft_strdup(environmentpath);
	pathsegments = ft_split(pathcopy, ':');
	if (pathsegments == NULL)
	{
		free(pathcopy);
		return (NULL);
	}
	if (pathsegments[0] != NULL)
		return (fullpath = ft_find(pathcopy, pathsegments, pathToFind));
	free(pathcopy);
	ft_free(pathsegments);
	return (NULL);
}

void	free_string_array(char **array)
{
	int	i;

	if (array)
	{
		i = 0;
		while (array[i])
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
}

int	ft_free_fd(int **fd, int num_cmds)
{
	int	i;

	i = 0;
	while (i < num_cmds - 1)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
	i = 0;
	while (i < num_cmds - 1)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
	i = 0;
	while (i < num_cmds)
	{
		wait(NULL);
		i++;
	}
	return (0);
}

int	ft_free_fdd(int **fd, int num_cmds)
{
	int	j;

	printf("Error: Fork failed.\n");
	j = -1;
	while (++j < num_cmds - 1)
		free(fd[j]);
	free(fd);
	return (1);
	j = -1;
	return (1);
}
