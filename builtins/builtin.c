/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelhaj- <mbelhaj-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 02:30:15 by flafi             #+#    #+#             */
/*   Updated: 2023/12/30 07:46:18 by mbelhaj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// removes quotes " and ' from a string
void	remove_quotes(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\"' && str[i] != '\'')
		{
			str[j] = str[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
}

void	ft_echo(char **cmd)
{
	int	n_flag;
	int	i;
	int printed;
	int k = 0;
	i = 1;
	n_flag = 0;
	if (!cmd[1])
	{
		write(1, "\n", 1);
		return ;
	}
	// while (cmd[k])
	// {
	// 	printf("----------->> {%s} \n",cmd[k]);
	// 	k++;
	// }
	if (cmd[1][0] == '-' && cmd[1][1] == 'n' && cmd[1][2] == '\0')
	{
		n_flag = 1;
		i = 2;
	}
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
}
// priting the pwd a.k.a cwd
void	ft_pwd(char **cmd, char **env)
{
	char	cwd[4096];

	(void)cmd;
	(void)env;
	getcwd(cwd, sizeof(cwd));
	// ft_putendl_fd(cwd, 1);
}

// get the current working directory
char	*get_cwd(void)
{
	char	cwd[4096];
	char	*path;

	path = NULL;
	getcwd(cwd, sizeof(cwd));
	path = cwd;
	return (path);
}
//  find the post of last slash (cd)
int	last_slash_pos(const char *str)
{
	int	len;

	len = ft_strlen(str);
	int position = -1;
	int i = len - 1;
	while (i >= 0)
	{
		if (str[i] == '/')
		{
			position = i;
			break ;
		}
		i--;
	}
	return (position);
}
// remove the last found slash (cd)
char	*rm_lastfld(char *cwd)
{
	char	*path;
	int		i;

	i = last_slash_pos(cwd);
	path = NULL;
	if (i != -1)
	{
		if (i == 0)
			return ("/");
		path = ft_substr(cwd, 0, i);
	}
	return (path);
}
// obviously for changing directory
void	ft_cd(char **cmd, t_cmd_inf minish)
{
	char	*home_path;
	char	*cdto_path;
    
    printf("after CMD ----- %s \n",cmd[0]);
	(void)minish;
	home_path = getenv("HOME");
	cdto_path = NULL;
	if (!home_path)
		home_path = "/";
	if (cmd[1] == NULL)
	{
		chdir(home_path);
		return ;
	}
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
	if (cdto_path != NULL && chdir(cdto_path) == -1)
	{
		ft_putstr_fd("MyShell: cd: ", 2);
		ft_putstr_fd(cdto_path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
}
// env for env lol
void	ft_env(t_cmd_inf minish)
{
	t_list	*current;

	current = minish.envlst;
	while (current != NULL)
	{
		ft_putendl_fd(current->content, 1);
		current = current->next;
	}
	minish.rtn_code = 0;
}

//  check if it is builtin or not
int	is_builtin(char **cmd, t_cmd_inf minish)
{
    char **str;
    str = ft_split(cmd[0], ' ');

	if (ft_strncmp(cmd[0], "echo", 4) == 0)
	{
		ft_echo(str); // i need to do the env variables
		return (0);
	}
	else if (ft_strncmp(cmd[0], "pwd", 3) == 0)
	{
		ft_pwd(cmd, minish.env);
		return (0);
	}
	else if (ft_strncmp(cmd[0], "cd", 2) == 0)
	{
        printf("before CMD ----- %s \n",cmd[0]);
		ft_cd(str, minish);
		return (0);
	}
	else if (ft_strncmp(cmd[0], "env", 3) == 0)
	{
		ft_env(minish);
		return (0);
	}
	else if (ft_strncmp(cmd[0], "export", 6) == 0)
	{
		ft_export(str, minish);
		return (0);
	}
	else if (ft_strncmp(cmd[0], "unset", 5) == 0)
	{
		ft_unset(str, minish);
		return (0);
	}
	else if (ft_strncmp(cmd[0], "exit", 4) == 0)
		exit(0); // verify the exit thingy
	// else if (ft_strncmp(cmd[0], "history", 7) == 0)
	//     {
	//         printf_hst(cmd, minish);
	//         return (0);
	//     }
	else
		return (1);
}
