/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 14:17:19 by mbelhaj-          #+#    #+#             */
/*   Updated: 2023/12/30 23:47:57 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//  find the post of last slash (cd)
int	last_slash_pos(const char *str)
{
	int	len;
	int	position;
	int	i;

	len = ft_strlen(str);
	position = -1;
	i = len - 1;
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

int	ft_run_builtin(t_cmd *cmd)
{
	if (ft_strncmp(cmd->final_cmd[0], "echo", 4) == 0)
		return (0);
	else if (ft_strncmp(cmd->final_cmd[0], "pwd", 3) == 0)
		return (0);
	else if (ft_strncmp(cmd->final_cmd[0], "cd", 2) == 0)
		return (0);
	else if (ft_strncmp(cmd->final_cmd[0], "env", 3) == 0)
		return (0);
	else if (ft_strncmp(cmd->final_cmd[0], "export", 6) == 0)
		return (0);
	else if (ft_strncmp(cmd->final_cmd[0], "unset", 5) == 0)
		return (0);
	else if (ft_strncmp(cmd->final_cmd[0], "exit", 4) == 0)
		return (0);
	else
		return (1);
}
