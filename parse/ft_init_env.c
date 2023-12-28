/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelhaj- <mbelhaj-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:26:20 by mbelhaj-          #+#    #+#             */
/*   Updated: 2023/12/20 15:44:18 by mbelhaj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_arrdup(char **arr)
{
	char	**rtn;
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	rtn = ft_calloc(sizeof(char *), i + 1);
	if (!rtn)
		return (NULL);
	i = 0;
	while (arr[i] != NULL)
	{
		rtn[i] = ft_strdup(arr[i]);
		if (rtn[i] == NULL)
		{
			ft_free_arr(rtn);
			return (rtn);
		}
		i++;
	}
	return (rtn);
}

int	ft_pwd(t_cmd_inf *c)
{
	int	i;

	i = 0;
	while (c->envp[i])
	{
		if (!ft_strncmp(c->envp[i], "PWD=", 4))
			c->pwd = ft_substr(c->envp[i],
					4, ft_strlen(c->envp[i]) - 4);
		if (!ft_strncmp(c->envp[i], "OLDPWD=", 7))
			c->old_pwd = ft_substr(c->envp[i],
					7, ft_strlen(c->envp[i]) - 7);
		i++;
	}
	return (1);
}

char	*find_path(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5));
		i++;
	}
	return (ft_strdup("\0"));
}

int	ft_get_envp(t_cmd_inf *c)
{
	char	*path_from_envp;
	int		i;
	char	*tmp;

	path_from_envp = find_path(c->envp);
	c->paths = ft_split(path_from_envp, ':');
	free(path_from_envp);
	i = 0;
	while (c->paths[i])
	{
		if (ft_strncmp(&c->paths[i][ft_strlen(c->paths[i]) - 1],
			"/", 1) != 0)
		{
			tmp = ft_strjoin(c->paths[i], "/");
			free(c->paths[i]);
			c->paths[i] = tmp;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
