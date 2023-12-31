/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 02:36:24 by flafi             #+#    #+#             */
/*   Updated: 2023/12/31 04:30:50 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*doexp_format(char *var_value, char *var_name)
{
	var_value = remove_qt(var_value);
	var_name = ft_strjoin(var_name, "=");
	var_name = ft_strjoin(var_name, "\"");
	var_name = ft_strjoin(var_name, var_value);
	var_name = ft_strjoin(var_name, "\"");
	return (var_name);
}

// if exists replace it or vice versa
int	check_exist_export(int pos, char *var_name, char *var_value,
		t_cmd_inf minish)
{
	t_list	*current;

	(void)pos;
	current = minish.envlst;
	while (current)
	{
		if (ft_strncmp(var_name, current->content, ft_strlen(var_name)) == 0)
		{
			if (pos == -1)
			{
				current->content = var_name;
				return (0);
			}
			current->content = doexp_format(var_value, var_name);
			return (0);
			break ;
		}
		current = current->next;
	}
	return (1);
}

void	add_or_replace(int pos, t_cmd_inf minish, char *var_name,
		char *var_value)
{
	if (check_exist_export(pos, var_name, var_value, minish) == 0)
		return ;
	if (pos == -1)
		ft_lstadd_back(&minish.envlst, ft_lstnew(remove_qt(var_name)));
	else
	{
		ft_lstadd_back(&minish.envlst, ft_lstnew(doexp_format(var_value,
					var_name)));
	}
}

// verify the allocaiton how its made and change it
// seprate func
int	ft_export(char **cmd, t_cmd_inf minish)
{
	int		i;
	int		pos;
	char	*var_name;
	char	*var_value;

	i = 0;
	var_name = NULL;
	var_value = NULL;
	if (!cmd[1])
		ft_export_print(minish);
	while (cmd[++i])
	{
		if (check_alphanum(cmd[i]) == 0)
		{
			ft_putstr_fd("bash: export: '", 2);
			ft_putstr_fd(cmd[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			minish.rtn_code = 1;
		}
		var_name = ft_substr(cmd[i], 0, find_value(cmd[i]));
		pos = find_value(cmd[i]);
		var_value = ft_substr(cmd[i], pos + 1, ft_strlen(cmd[i]) - pos - 1);
		add_or_replace(pos, minish, var_name, var_value);
	}
	return (minish.rtn_code = 0, 0);
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
