/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 21:31:28 by mbelhaj-          #+#    #+#             */
/*   Updated: 2023/12/30 23:00:27 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free(char **str)
{
	int	i;

	if (str == NULL)
		return ;
	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

// Close unused read end of the pipe
// Redirect stdout to the write end of the pipe
// Close the write end of the pipe
void	ft_child(char *cmd1, char **envp, int *fd)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	ft_execve(cmd1, envp);
}

// Close the write end of the pipe
// Redirect stdin to the read end of the pipe
// Close the read end of the pipe
// Execute cmd2
void	ft_parent(char *cmd2, char **envp, int *fd)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	ft_execve(cmd2, envp);
}

char	*ft_getenv(const char *var_name, char **envp)
{
	size_t	var_name_len;
	int		i;

	if (var_name == NULL || envp == NULL)
	{
		return (NULL);
	}
	var_name_len = ft_strlen(var_name);
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(var_name, envp[i], var_name_len) == 0
			&& envp[i][var_name_len] == '=')
		{
			return (&envp[i][var_name_len + 1]);
		}
		i++;
	}
	return (NULL);
}
