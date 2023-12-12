/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 21:56:08 by flafi             #+#    #+#             */
/*   Updated: 2023/12/12 22:00:16 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// move to the echo file
// temp echo not finished
void ft_echo(char **cmd)
{
    int n_flag;
    int i;
    
    i = 0;
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
        // printf("flag is UP!\n");
    }
    while(cmd[i])
    {
        printf("%s ", cmd[i]); // better solution
        if (!cmd[i + 1] && !n_flag)
            printf("\n");
        i++;
    }

}

//  check if it is builtin or not
int is_builtin(char **cmd)
{
    if (ft_strncmp(cmd[0], "echo", 4) == 0)
    {
        // char *str = "we detected an echo\n";
        ft_echo(cmd);
        return (0);
    }
    // else if (ft_strncmp(cmd, "cd", 2) == 0)
    //     return 1;
    // else if (ft_strcmp(cmd, "pwd") == 0)
    //     return 1;
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