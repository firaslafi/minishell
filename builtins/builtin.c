/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 02:30:15 by flafi             #+#    #+#             */
/*   Updated: 2023/12/30 22:35:20 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_check_nflag(char **cmd, int *n_flag, int *i)
{
	if (cmd[1][0] == '-' && cmd[1][1] == 'n' && cmd[1][2] == '\0')
	{
		*n_flag = 1;
		*i = 2;
	}
}

int	ft_echo(char **cmd)
{
	int	n_flag;
	int	i;
	int	printed;

	i = 1;
	n_flag = 0;
	if (!cmd[1])
		return (write(1, "\n", 1), 1);
	ft_check_nflag(cmd, &n_flag, &i);
	printed = 0;
	while (cmd[i] != NULL)
	{
		remove_quotes(cmd[i]);
		write(1, cmd[i], ft_strlen(cmd[i]));
		printed = 1;
		if (cmd[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (!n_flag && printed)
		write(1, "\n", 1);
	return (0);
}
// priting the pwd a.k.a cwd
int	ft_pwd(char **cmd, char **env)
{
	char	cwd[4096];

	(void)cmd;
	(void)env;
	getcwd(cwd, sizeof(cwd));
	ft_putendl_fd(cwd, 1);
	return (0);
}

char	*ft_get_cd(char **cmd)
{
	char	*cdto_path;
	char	*home_path;

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

//  check if it is builtin or not
// i need to do the env variables
int	is_builtin(char **cmd, t_cmd_inf minish)
{
	char	**str;

	str = ft_split(cmd[0], ' ');
	// handle switching here
	
	// 
	if (ft_strncmp(cmd[0], "echo", 4) == 0)
		return (minish.rtn_code = ft_echo(str), minish.rtn_code);
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
