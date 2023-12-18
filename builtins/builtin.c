/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 21:56:08 by flafi             #+#    #+#             */
/*   Updated: 2023/12/18 19:40:02 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// move to the echo file
// temp echo not finished
//  work on the $variables

// removes quotes " and ' from a string
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
// priting the pwd a.k.a cwd
void ft_pwd(char **cmd, char **env)
{

    (void)cmd;
    (void)env;

    char cwd[4096];
    getcwd(cwd, sizeof(cwd));
    // ft_putendl_fd(pwd, 1);
    ft_putendl_fd(cwd, 1);
}
// get the current working directory
char *get_cwd()
{
    char cwd[4096];
    char *path;
    
    path = NULL;
    getcwd(cwd, sizeof(cwd));
    path = cwd;
    return (path);
}
//  find the post of last slash (cd)
int last_slash_pos(const char *str)
{
    int len = ft_strlen(str);
    int position = -1; // Default position if no slash is found
    int i = len - 1; // Start from the end of the string
    
    while (i >= 0) 
    {
        if (str[i] == '/') {
            position = i;
            break;
        }
        i--;
    }
    return position;
}
// remove the last found slash (cd)
char *rm_lastfld(char *cwd)
{
    char *path;
    int i;
    
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
void ft_cd(char **cmd, t_mini minish)
{
    char *home_path;
    char *cdto_path;
    
    (void)minish;
    home_path = getenv("HOME");
    cdto_path = NULL;
    if(!home_path)
        home_path = "/";
    if (cmd[1] == NULL)
        {
            chdir(home_path);
            return;
        }
    if (cmd[1] != NULL)
    {
        if (ft_strncmp(cmd[1], "-", 1) == 0)
        {
            cdto_path = getenv("OLDPWD");
            if(!cdto_path)
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
void ft_env(t_mini minish)
{
    t_list *current;
    
    current = minish.envlst;
    while (current != NULL) 
    {
        ft_putendl_fd(current->content, 1);
        current = current->next;
    }
}



//  check if it is builtin or not
int is_builtin(char **cmd, t_mini minish)
{
    if (ft_strncmp(cmd[0], "echo", 4) == 0)
    {
        ft_echo(cmd); // i need to do the env variables
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
    else if (ft_strncmp(cmd[0], "env", 3) == 0)
        {
            ft_env(minish);
            return (0);
        }
    else if (ft_strncmp(cmd[0], "export", 6) == 0)
        {
            ft_export(cmd, minish);
            return (0);
        }
    else if (ft_strncmp(cmd[0], "unset", 5) == 0)
        {
            ft_unset(cmd, minish);
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
        return 1;
}

// printf_hst