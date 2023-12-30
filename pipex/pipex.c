/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelhaj- <mbelhaj-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 19:26:15 by mbelhaj-          #+#    #+#             */
/*   Updated: 2023/12/30 21:01:28 by mbelhaj-         ###   ########.fr       */
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

void	ft_execve(char *argv, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	if (!cmd)
		return (printf("Error: Unable to split command.\n"), (void)0);
	if (cmd[0][0] == '/')
	{
		if (access(cmd[0], X_OK) == 0)
			path = cmd[0];
		else
			printf("no access or invalid\n");
	}
	else
		path = ft_path(cmd[0], envp);
	if (!path)
	{
		printf("Error: Command '%s' not found in PATH.\n", cmd[0]);
		free_string_array(cmd);
		return ;
	}
	execve(path, cmd, envp);
	perror("execve error");
	free(path);
	free_string_array(cmd);
}

int	ft_heredoc(t_cmd *cmds, int fd)
{
	if (ft_strncmp(cmds->flags, "L_LG_G", 6) == 0)
		fd = open(cmds->output, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if ((ft_strncmp(cmds->flags, "L_LG", 4) == 0))
		fd = open(cmds->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (ft_strncmp(cmds->flags, "L_L", 3) == 0)
		fd = open(cmds->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (fd);
}

int	ft_open_here(t_cmd *cmds)
{
	char	*doc;
	char	*limiter;
	int		ipc[2];
	int		fd;

	if (pipe(ipc))
		return (0);
	limiter = ft_strjoin(cmds->here_doc, "\n");
	doc = get_next_line(0);
	while (doc && ft_strncmp(limiter, doc, ft_strlen(doc)))
	{
		ft_putstr_fd(doc, ipc[1]);
		free(doc);
		doc = get_next_line(0);
	}
	free(limiter);
	if (doc)
		free(doc);
	dup2(ipc[0], 0);
	fd = ft_heredoc(cmds, fd);
	dup2(fd, 1);
	close(ipc[0]);
	close(ipc[1]);
	return (0);
}

void	ft_read_red(t_cmd *cmds)
{
	int	fd_input;
	int	fd_output;

	fd_input = open(cmds->input, O_RDONLY, 0644);
	fd_output = open(cmds->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_output == -1)
		close(fd_output);
	dup2(fd_input, STDIN_FILENO);
	dup2(fd_output, STDOUT_FILENO);
	close(fd_input);
	close(fd_output);
}

void	ft_read_write(t_cmd *cmds)
{
	int	fd_ops;
	int	fd_op;

	fd_ops = open(cmds->input, O_RDONLY, 0644);
	if (fd_ops == -1)
	{
		printf("%s : No such file or directory", cmds->input);
		return ;
	}
	fd_op = open(cmds->output, O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(fd_ops, STDIN_FILENO);
	dup2(fd_op, STDOUT_FILENO);
	close(fd_ops);
	close(fd_op);
}

void	ft_read_write_red(t_cmd *cmds)
{
	int	fd_op;
	int	fd_ops;

	if (ft_strncmp(cmds->flags, "G_G", 3) == 0)
	{
		fd_op = open(cmds->output, O_WRONLY | O_CREAT | O_APPEND, 0644);
		dup2(fd_op, STDOUT_FILENO);
	}
	else if (ft_strncmp(cmds->flags, "G", 1) == 0)
	{
		fd_op = open(cmds->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd_op, STDOUT_FILENO);
	}
	else if (ft_strncmp(cmds->flags, "L", 1) == 0)
	{
		fd_ops = open(cmds->input, O_RDONLY, 0644);
		if (fd_ops == -1)
		{
			printf("%s : No such file or directory", cmds->input);
			return ;
		}
		dup2(fd_ops, STDIN_FILENO);
		close(fd_ops);
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

int	**ft_malloc_fd(int **fd, int num_cmds)
{
	int	i;

	i = 0;
	while (i < num_cmds - 1)
	{
		fd[i] = malloc(sizeof(int) * 2);
		if (!fd[i] || pipe(fd[i]) == -1)
		{
			printf("Error: Pipe creation failed.\n");
			while (--i >= 0)
				free(fd[i]);
			free(fd);
		}
		i++;
	}
	return (fd);
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
void	ft_close_fd(int **fd, int num_cmds)
{
	int	j;

	j = 0;
	while (j < num_cmds - 1)
	{
		close(fd[j][0]);
		close(fd[j][1]);
		j++;
	}
}

void	ft_put_flag(t_cmd *cmds, int i, int num_cmds)
{
	if (i == num_cmds - 1)
	{
		if (cmds->here_doc != NULL)
			ft_open_here(cmds);
		if (ft_strncmp(cmds->flags, "LG", 2) == 0)
			ft_read_red(cmds);
		else if (ft_strncmp(cmds->flags, "LG_G", 4) == 0)
			ft_read_write(cmds);
		else
			ft_read_write_red(cmds);
	}
}
void	ft_dup2(int **fd, int i, int num_cmds)
{
	if (i > 0)
		dup2(fd[i - 1][0], STDIN_FILENO);
	if (i < num_cmds - 1)
		dup2(fd[i][1], STDOUT_FILENO);
}

int	pipex(t_cmd *cmds, char **envp, int num_cmds)
{
	int		**fd;
	pid_t	pid;
	int		i;

	fd = malloc(sizeof(int *) * (num_cmds - 1));
	if (!fd)
		return (printf("Error: Memory allocation failed.\n"), 1);
	fd = ft_malloc_fd(fd, num_cmds);
	i = -1;
	while (++i < num_cmds)
	{
		pid = fork();
		if (pid == -1)
			return (ft_free_fdd(fd, num_cmds));
		else if (pid == 0)
		{
			ft_dup2(fd, i, num_cmds);
			ft_close_fd(fd, num_cmds);
			ft_put_flag(cmds, i, num_cmds);
			ft_execve(cmds->final_cmd[i], envp);
			exit(EXIT_FAILURE);
		}
	}
	return (ft_free_fd(fd, num_cmds), 0);
}
