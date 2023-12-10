/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:19:21 by flafi             #+#    #+#             */
/*   Updated: 2023/12/10 23:20:06 by flafi            ###   ########.fr       */
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

void add_history_front(t_historylist **history, t_historylist *newEntry)
{
    // Add the entry to the front of the list
    newEntry->next = *history;
    *history = newEntry;

}

// Create a new history entry & add to the front of the list
void ft_add_history(const char *command, t_historylist **history, t_mem_block **lst)
{
    // Create a new history entry
    t_historylist *newEntry = ft_malloc(lst, sizeof(t_historylist));
    // do a rework for strdup or add to the lst free
    newEntry->command = ft_strdup_s(command, lst);
    newEntry->next = NULL;
    add_history_front(history, newEntry);
}
    // t_historylist *history = NULL;
        // t_historylist *current = history;

        // printf("History:\n");
        //     while (current != NULL)
        //     {
        //         printf("%d: %s\n", index++, current->command);
        //         current = current->next;
        //     }
// call ft_add_history(input, &history, &lst);
/* above is pointless*//* above is pointless*/
/* above is pointless*//* above is pointless*/


int main(int argc, char **env)
{
    // char *input;
    t_mem_block *lst = NULL;
    // char **token;
    (void)env;
    
    if (argc != 1)
    {
        printf("error\n");
        exit(1);
    }
    //  testing here
    
    // env copy
    char *envcpy = ft_malloc(&lst, ft_strlen(*env) + 1);
    ft_strcpy(envcpy, *env);
    printf("env = %s", envcpy);
    //  i need to make it copy full 2D
    
    // while(1)
    // {
    //     input = readline(ANSI_COLOR_GREEN"MyShell$ "ANSI_COLOR_RESET);
    //     if (input[0] != '\0')
    //     {
    //         //  check if it is builtin or not
    //         // if it is builtin i need to call a fucntion to excute the bultints 
    //         add_history(input);
    //         free(input);
    //     }
    //     token = history_tokenize(input);
    //     printf("last token= %s\n", *token);
    // }
    ft_free_all(&lst);
    

    // printf("PATH : %s\n", getenv("PATH"));
    // printf("HOME : %s\n", getenv("HOME"));
    // printf("ROOT : %s\n", getenv("ROOT"));
    return(0);
}
