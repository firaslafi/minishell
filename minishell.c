/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:19:21 by flafi             #+#    #+#             */
/*   Updated: 2023/12/04 18:15:00 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"
// working on a prompt and loop
// void ()
int main(int argc, char **argv, char **env)
{
    // (void)argc;
    (void)argv;
    (void)env;
    
    if (argc == 1)
    {
        printf(ANSI_COLOR_GREEN "MyShell> " ANSI_COLOR_RESET);
        while(1)
        {
            // exit(1);
        }
    }
    else
    {
        printf("error\n");    
    }
    // printf("PATH : %s\n", getenv("PATH"));
    // printf("HOME : %s\n", getenv("HOME"));
    // printf("ROOT : %s\n", getenv("ROOT"));
    return(0);
}
