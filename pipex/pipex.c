/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 19:26:15 by mbelhaj-          #+#    #+#             */
/*   Updated: 2023/12/30 23:38:58 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
