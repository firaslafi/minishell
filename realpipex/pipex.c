/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 19:26:15 by mbelhaj-          #+#    #+#             */
/*   Updated: 2023/12/28 06:13:50 by flafi            ###   ########.fr       */
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

void free_string_array(char **array) {
    if (array) {
        int i = 0;
        while (array[i]) {
            free(array[i]);
            i++;
        }
        free(array);
    }
}

void ft_execve(char *argv, char **envp) {
    printf("Executing command: %s\n", argv); // Diagnostic print

    char **cmd = ft_split(argv, ' ');
    if (!cmd) {
        fprintf(stderr, "Error: Unable to split command.\n");
        return;
    }

    char *path = ft_path(cmd[0], envp);
    if (!path) {
        fprintf(stderr, "Error: Command '%s' not found in PATH.\n", cmd[0]);
        free_string_array(cmd);
        return;
    }

    printf("Command path resolved: %s\n", path); // Diagnostic print

    execve(path, cmd, envp);
    perror("execve error"); // Diagnostic print, perror will print the last system error

    // Clean up allocated memory - this will only run if execve fails
    free(path);
    free_string_array(cmd);
}


int pipex(char **cmds, char **envp, int num_cmds) {
    int i, j;
    int **fd = malloc(sizeof(int *) * (num_cmds - 1));

    if (!fd) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return 1;
    }

    for (i = 0; i < num_cmds - 1; i++) {
        fd[i] = malloc(sizeof(int) * 2);
        if (!fd[i] || pipe(fd[i]) == -1) {
            fprintf(stderr, "Error: Pipe creation failed.\n");
            // Cleanup previously allocated pipes
            while (--i >= 0) {
                free(fd[i]);
            }
            free(fd);
            return 1;
        }
    }

    for (i = 0; i < num_cmds; i++) {
        pid_t pid = fork();

        if (pid == -1) {
            fprintf(stderr, "Error: Fork failed.\n");
            // Cleanup pipes
            for (j = 0; j < num_cmds - 1; j++) {
                free(fd[j]);
            }
            free(fd);
            return 1;
        } else if (pid == 0) { // Child process
            if (i > 0) {
                dup2(fd[i - 1][0], STDIN_FILENO); // Redirect stdin from the previous pipe
            }
            if (i < num_cmds - 1) {
                dup2(fd[i][1], STDOUT_FILENO); // Redirect stdout to the next pipe
            }
            // Close all pipes in child process
            for (j = 0; j < num_cmds - 1; j++) {
                close(fd[j][0]);
                close(fd[j][1]);
            }
            ft_execve(cmds[i], envp);
            exit(EXIT_FAILURE); // If execve fails, exit child with error code
        }
    }

    // Close all pipes in the parent process
    for (i = 0; i < num_cmds - 1; i++) {
        close(fd[i][0]);
        close(fd[i][1]);
        free(fd[i]);
    }
    free(fd);

    // Wait for all child processes to complete
    for (i = 0; i < num_cmds; i++) {
        wait(NULL);
    }

    return 0;
}
