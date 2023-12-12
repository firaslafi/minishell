/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:19:21 by flafi             #+#    #+#             */
/*   Updated: 2023/12/11 18:44:55 by flafi            ###   ########.fr       */
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

char  **make_encpy(char **envp, t_mem_block *lst)
{
    int envp_size = 0;
    while (envp[envp_size]) 
    {
        envp_size++;
    }
    char **envcpy = ft_malloc(&lst, (envp_size + 1) * sizeof(char *));
    // Allocate memory for envcpy
    if (envcpy == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    int i = 0;
    while (envp[i]) 
    {
        // Allocate memory for each environment variable and copy its content
        envcpy[i] = ft_strdup_s(envp[i], &lst);
        i++;
    }
     envcpy[i] = NULL;
     return (envcpy);
}

int	main(int argc, char **argv, char **envp)
{
    char *input;
    t_mem_block *lst = NULL;
    char **token;
    (void)argv;
    
    if (argc != 1)
    {
        printf("error\n");
        exit(1);
    }
    //  testing here
    char **envcpy = make_encpy(envp, lst);
    (void)envcpy;
    // (void)envp;
    // (void)lst;

    while (1)
    {
        input = readline(ANSI_COLOR_GREEN"MyShell$ "ANSI_COLOR_RESET);

        if (input[0] != '\0') 
        {
            add_history(input);
            token = history_tokenize(input);
            free(input);
        }
        
        printf("cmd = %s\n", *token);
        free(token);
    }
    ft_free_all(&lst);
    
    // system("leaks minishell");
    
    // printf("PATH : %s\n", getenv("PATH"));
    // printf("HOME : %s\n", getenv("HOME"));
    // printf("ROOT : %s\n", getenv("ROOT"));
    return(0);
}
