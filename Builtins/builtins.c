/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 21:56:08 by flafi             #+#    #+#             */
/*   Updated: 2023/12/11 18:52:29 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

//  check if it is builtin or not
int is_builtin(char *cmd)
{
    if (ft_strcmp(cmd, "echo") == 0 && /* check for options */) {
        // handle echo command with options
        return 1;
    } else if (ft_strcmp(cmd, "cd") == 0 && /* check for relative/absolute path */) {
        // handle cd command with a path
        return 1;
    } else if (ft_strcmp(cmd, "pwd") == 0) {
        // handle pwd command
        return 1;
    } else if (ft_strcmp(cmd, "export") == 0) {
        // handle export command
        return 1;
    } else if (ft_strcmp(cmd, "unset") == 0) {
        // handle unset command
        return 1;
    } else if (ft_strcmp(cmd, "env") == 0) {
        // handle env command
        return 1;
    } else if (ft_strcmp(cmd, "exit") == 0) {
        // handle exit command
        return 1;
    } else
        return 0; // Not a built-in command
}


// funct for all bultins
//  if else statement for if cd pwd echo export
// relative or absolute path /bin/ls or ls
// if str[0] == / then verify path else i need to find the path for ls