/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelhaj- <mbelhaj-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 19:26:15 by mbelhaj-          #+#    #+#             */
/*   Updated: 2023/12/30 07:09:11 by mbelhaj-         ###   ########.fr       */
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

	// printf("Executing command: %s\n", argv); // Diagnostic print
	cmd = ft_split(argv, ' ');
	if (!cmd)
	{
		fprintf(stderr, "Error: Unable to split command.\n");
		return ;
	}
	if (cmd[0][0] == '/')
    {
        if (access(cmd[0], X_OK) == 0)
            path = cmd[0];
        else
            printf("no access or invalid\n");
    }
    else
    {
       path = ft_path(cmd[0], envp);
    }
	// path = ft_path(cmd[0], envp);
	if (!path)
	{
		fprintf(stderr, "Error: Command '%s' not found in PATH.\n", cmd[0]);
		free_string_array(cmd);
		return ;
	}
	// printf("Command path resolved: %s\n", path); // Diagnostic print
	execve(path, cmd, envp);
	perror("execve error"); // Diagnostic print,
		// perror will print the last system error
	// Clean up allocated memory - this will only run if execve fails
	free(path);
	free_string_array(cmd);
}

int	pipex(t_cmd *cmds, char **envp, int num_cmds)
{
	int		**fd;
	pid_t	pid;

	int i, j;
	fd = malloc(sizeof(int *) * (num_cmds - 1));
	if (!fd)
	{
		fprintf(stderr, "Error: Memory allocation failed.\n");
		return (1);
	}
	for (i = 0; i < num_cmds - 1; i++)
	{
		fd[i] = malloc(sizeof(int) * 2);
		if (!fd[i] || pipe(fd[i]) == -1)
		{
			fprintf(stderr, "Error: Pipe creation failed.\n");
			// Cleanup previously allocated pipes
			while (--i >= 0)
			{
				free(fd[i]);
			}
			free(fd);
			return (1);
		}
	}
	for (i = 0; i < num_cmds; i++)
	{
		pid = fork();
		if (pid == -1)
		{
			fprintf(stderr, "Error: Fork failed.\n");
			// Cleanup pipes
			for (j = 0; j < num_cmds - 1; j++)
			{
				free(fd[j]);
			}
			free(fd);
			return (1);
		}
		else if (pid == 0)
		{ // Child process
			if (i > 0)
			{
				dup2(fd[i - 1][0], STDIN_FILENO);
					// Redirect stdin from the previous pipe
			}
			if (i < num_cmds - 1)
			{
				dup2(fd[i][1], STDOUT_FILENO);
					// Redirect stdout to the next pipe
			}
			// Close all pipes in child process
			for (j = 0; j < num_cmds - 1; j++)
			{
				close(fd[j][0]);
				close(fd[j][1]);
			}
            
            if (i == num_cmds - 1) 
            {

                //  WE NEED TO PROTECT THE OPENING OF FDS !!!!
                
                // cmd->output
                // if one > do this
                
                // int fd_op = open("file1", O_WRONLY | O_CREAT | O_TRUNC, 0644);
                // dup2(fd_op, STDOUT_FILENO);

                // else >> do this
                
                // int fd_op = open("file1", O_WRONLY | O_CREAT | O_APPEND, 0644);
                // dup2(fd_op, STDOUT_FILENO);

                // redirection stuff 
                
                // this one should be inside the loop works as a single command
                // if one < do this
                
                // cmd->input
                // int pip;
                // pipe(pip);
                // int fd_ops = open("file1", O_RDONLY, 0644);
                // dup2(fd_ops, STDIN_FILENO);
                // close(fd_ops);
                
                // cat < blablablaHERE.txt | cat < test.xt
                // cat

                /********************* here_doc**************/
                if (cmds->here_doc != NULL)
                {
        
                    char    *doc;
                    char    *limiter;
                    int     ipc[2];
					int		fd;
                    
                    printf("----------> 5%s \n",cmds->here_doc);
                    if (pipe(ipc))
                       return(0);   
                    limiter = ft_strjoin(cmds->here_doc,"\n");
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
					if (ft_strcmp(cmds->flags,"L_LG") == 0)
						fd = open(cmds->output, O_WRONLY | O_CREAT| O_TRUNC, 0644);
					else
						fd = open(cmds->output, O_WRONLY | O_CREAT| O_APPEND, 0644);
                    dup2(fd, 1);
                    close(ipc[0]);
                    close(ipc[1]);

                }
                /********************* here_doc**************/
                
                if (ft_strcmp(cmds->flags,"LG") == 0)
                {
                    printf("----------> 1%s \n",cmds->here_doc);

                    int fd_input = open(cmds->input, O_RDONLY, 0644);
                    int fd_output = open(cmds->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
					if (fd_output == -1)
						close(fd_output);
					dup2(fd_input, STDIN_FILENO);
                	dup2(fd_output, STDOUT_FILENO);
					close(fd_input);
					close(fd_output);
                }
				else if (ft_strcmp(cmds->flags,"LG_G") == 0)
                {
                    printf("----------> 1%s \n",cmds->here_doc);

                    int fd_ops = open(cmds->input, O_RDONLY, 0644);
                    int fd_op = open(cmds->output, O_WRONLY | O_CREAT | O_APPEND, 0644);
					dup2(fd_ops, STDIN_FILENO);
                	dup2(fd_op, STDOUT_FILENO);
					close(fd_ops);
					close(fd_op);
                }
				else if (ft_strcmp(cmds->flags,"G") == 0)
				{
                    printf("----------> 2%s \n",cmds->here_doc);

					int fd_op = open(cmds->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                	dup2(fd_op, STDOUT_FILENO);
				}
				else if (ft_strcmp(cmds->flags,"G_G") == 0)
				{
                    printf("----------> 3%s \n",cmds->here_doc);

				 	int fd_op = open(cmds->output, O_WRONLY | O_CREAT | O_APPEND, 0644);
                	dup2(fd_op, STDOUT_FILENO);	
				}
				else if (ft_strcmp(cmds->flags,"L") == 0)
				{
                    printf("----------> 4%s \n",cmds->here_doc);

					int fd_ops = open(cmds->input, O_RDONLY, 0644);
					dup2(fd_ops, STDIN_FILENO);
					close(fd_ops);
				}

            }
                
			ft_execve(cmds->final_cmd[i], envp);
			exit(EXIT_FAILURE); // If execve fails, exit child with error code
		}
	}
	// Close all pipes in the parent process
	for (i = 0; i < num_cmds - 1; i++)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		free(fd[i]);
	}
	free(fd);
	// Wait for all child processes to complete
	for (i = 0; i < num_cmds; i++)
	{
		wait(NULL);
	}
	return (0);
}

