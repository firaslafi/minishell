/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_related.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 23:05:44 by flafi             #+#    #+#             */
/*   Updated: 2023/12/30 23:14:02 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
