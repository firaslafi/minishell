/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 21:56:08 by flafi             #+#    #+#             */
/*   Updated: 2023/12/13 23:04:57 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// move to the echo file
// temp echo not finished
// void ft_quotes()
void remove_quotes(char *str)
{
    int i = 0;
    int j = 0;
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

void ft_echo(char **cmd)
{
    int n_flag;
    int i;
    
    i = 1;
    n_flag = 0;
    if (!cmd[1])
    {
        write(1, "\n", 1);
        return;
    }
    if (cmd[1][0] == '-' && cmd[1][1] == 'n' && cmd[1][2] == '\0')
    {
        n_flag = 1;
        i = 2;
    }
    int printed = 0; // To track whether anything has been printed
    while (cmd[i] != NULL) 
    {
        remove_quotes(cmd[i]);
        write(1, cmd[i], ft_strlen(cmd[i]));
        printed = 1;
        if (cmd[i + 1] != NULL) 
            write(1, " ", 1); // Print a space between arguments
        i++;
    }
    if (!n_flag && printed) // Add a newline if not -n and something was printed
        write(1, "\n", 1);

}
void ft_pwd(char **cmd, char **env)
{
    char *pwd;
    int i;
    (void)cmd;
	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PWD", 3))
			break ;
		i++;
	}
    pwd = ft_substr(env[i], 4, ft_strlen(env[i]) - 4);
    ft_putendl_fd(pwd, 1);
}

void ft_cd(char **cmd, t_mini minish)
{
    char *home_path;
    (void)minish;
    home_path = getenv("HOME");
    if(!home_path)
        home_path = "/";
    if (cmd[1] != NULL)
    {
        if (ft_strncmp(cmd[1], "-", 1) == 0)
        {
            if(!getenv("OLDPWD"))
                ft_putendl_fd("cd: OLDPWD not set", 2);
            else
            {
                printf("we need to CD !! with error handling\n");
            }
        }
    }
    // free(home_path);
}
//  check if it is builtin or not
int is_builtin(char **cmd, t_mini minish)
{
    if (ft_strncmp(cmd[0], "echo", 4) == 0)
    {
        ft_echo(cmd);
        return (0);
    }
    else if (ft_strncmp(cmd[0], "pwd", 3) == 0)
        {
            ft_pwd(cmd, minish.env);
            return (0);
        }
    else if (ft_strncmp(cmd[0], "cd", 2) == 0)
        {
            ft_cd(cmd, minish);
            return (0);
        }
    // else if (ft_strcmp(cmd, "export") == 0)
    //     return 1;
    // else if (ft_strcmp(cmd, "unset") == 0)
    //     return 1;
    // else if (ft_strcmp(cmd, "env") == 0)
    //     return 1;
    // else if (ft_strcmp(cmd, "exit") == 0)
    //     return 1;
    else
        return 1;
}


// funct for all bultins
//  if else statement for if cd pwd echo export
// relative or absolute path /bin/ls or ls
// if str[0] == / then verify path else i need to find the path for ls