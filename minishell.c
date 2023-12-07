/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:19:21 by flafi             #+#    #+#             */
/*   Updated: 2023/12/07 20:03:09 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"
// working on a prompt and loop

// char **token;
// token = history_tokenize(input);
// add_history(input);
// if (token[0])
// {
//     if (strcmp(token[0], "pwd") == 0)
//        excute
// }
// exit(1);
// envpp.env = function_duplication(env);
// t_glob envpp;
int main(int argc, char **argv, char **env)
{
    char *input;
    (void)argv;
    (void)env;

    if (argc != 1)
    {
        printf("error\n");
        exit(1);
    }
    char *rkwt = ft_strdup("hello");
    printf("%s\n", rkwt);
    while(1)
    {
        input = readline(ANSI_COLOR_GREEN"MyShell$ "ANSI_COLOR_RESET);
        add_history(input);
    }
    // free(input);

    // printf("PATH : %s\n", getenv("PATH"));
    // printf("HOME : %s\n", getenv("HOME"));
    // printf("ROOT : %s\n", getenv("ROOT"));
    return(0);
}
