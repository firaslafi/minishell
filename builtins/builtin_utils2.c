/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 04:26:14 by flafi             #+#    #+#             */
/*   Updated: 2023/12/31 04:27:10 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_get_cd(char **cmd)
{
	char	*cdto_path;
	char	*home_path;

	cdto_path = NULL;
	home_path = NULL;
	if (cmd[1] != NULL)
	{
		if (ft_strncmp(cmd[1], "-", 1) == 0)
		{
			cdto_path = getenv("OLDPWD");
			if (!cdto_path)
				ft_putendl_fd("cd: OLDPWD not set", 2);
		}
		else if (ft_strncmp(cmd[1], "~", 1) == 0)
			cdto_path = home_path;
		else if (ft_strncmp(cmd[1], "..", 2) == 0)
			cdto_path = rm_lastfld(get_cwd());
		else
			cdto_path = cmd[1];
	}
	return (cdto_path);
}

int	ft_cd(char **cmd, t_cmd_inf minish)
{
	char	*home_path;
	char	*cdto_path;

	(void)minish;
	home_path = getenv("HOME");
	cdto_path = NULL;
	if (!home_path)
		home_path = "/";
	if (cmd[1] == NULL)
	{
		chdir(home_path);
		return (1);
	}
	cdto_path = ft_get_cd(cmd);
	if (cdto_path != NULL && chdir(cdto_path) == -1)
	{
		ft_putstr_fd("MyShell: cd: ", 2);
		ft_putstr_fd(cdto_path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	return (0);
}

// to move somewhere else
// strchr for token 2d
int	ft_strchr_2d(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (ft_strchr(array[i], '$') != NULL)
			return (1);
		i++;
	}
	return (0);
}

void	ft_handle_var(char **cmd, t_cmd_inf minish)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (ft_strncmp(&cmd[i][j], "$", 1) != 0)
			j++;
		check_exist_envp(cmd[i], minish);
		i++;
	}
}

//  check if it is builtin or not
// i need to do the env variables
int	is_builtin(char **cmd, t_cmd_inf minish)
{
	char	**str;

	str = ft_split(cmd[0], ' ');
	if (ft_strncmp(cmd[0], "echo", 4) == 0)
		return (minish.rtn_code = ft_echo(str, minish), minish.rtn_code);
	else if (ft_strncmp(cmd[0], "pwd", 3) == 0)
		return (minish.rtn_code = ft_pwd(cmd, minish.env), minish.rtn_code);
	else if (ft_strncmp(cmd[0], "cd", 2) == 0)
		return (minish.rtn_code = ft_cd(str, minish), minish.rtn_code);
	else if (ft_strncmp(cmd[0], "env", 3) == 0)
		return (minish.rtn_code = ft_env(minish), minish.rtn_code);
	else if (ft_strncmp(cmd[0], "export", 6) == 0)
		return (ft_export(str, minish), minish.rtn_code);
	else if (ft_strncmp(cmd[0], "unset", 5) == 0)
		return (minish.rtn_code = ft_unset(str, minish), minish.rtn_code);
	else if (ft_strncmp(cmd[0], "exit", 4) == 0)
	{
		ft_free_all(&minish.lst);
		exit(0);
	}
	else
		return (1);
}
