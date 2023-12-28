/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 02:36:24 by flafi             #+#    #+#             */
/*   Updated: 2023/12/28 02:37:00 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_export_print(t_cmd_inf minish)
{
    t_list *current;
    
    current = minish.envlst;
    while (current != NULL) 
    {
        ft_putstr_fd("declare -x ", 1);
        ft_putendl_fd(current->content, 1);
        current = current->next;
    }
}
// looks for the = and quotes and return the pos first chr of the value
// 39 is the ascii of '
int find_value(char *str)
{
    int i;
    int len;
    int pos;
    
    i = 0;
    len = ft_strlen(str);
    pos = -1;
    while(i < len)
    {
        if (str[i] == '=')
            {
                pos = i;
                break;
            }
        i++;
    }
    // if (pos != -1 && (str[pos + 1] == '\"' || str[pos + 1] == '\''))
    //     pos = pos ;
    return (pos);
}

// first char should not be number and should be alpha numeritic min 1 chr
int check_alphanum(char *str)
{
    if (ft_isdigit(str[0]) == 1)
        return (0);
    if (ft_isalpha(str[0]) == 1)
        return (1);
    if (str[1] != '\0' && ft_isalpha(str[1]) == 1)
        return (1);
    else
        return (0);
}

char *remove_qt(char *str)
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
    return(str);
}
char *doexp_format(char *var_value, char *var_name)
{
    var_value = remove_qt(var_value);
    var_name = ft_strjoin(var_name, "=");
    var_name = ft_strjoin(var_name, "\"");
    var_name = ft_strjoin(var_name, var_value);
    var_name = ft_strjoin(var_name, "\"");
    return (var_name);
}
// if exists replace it or vice versa
int check_exist_export(int pos, char *var_name, char *var_value, t_cmd_inf minish)
{
    t_list *current;
    
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
                break;
            }
        current = current->next;
    }
    return (1);
}


void add_or_replace(int pos, t_cmd_inf minish, char *var_name, char *var_value)
{
    if (check_exist_export(pos, var_name, var_value, minish) == 0)
        return;
    if (pos == -1)
        ft_lstadd_back(&minish.envlst, ft_lstnew(remove_qt(var_name)));
    else
    {
        ft_lstadd_back(&minish.envlst, ft_lstnew(doexp_format(var_value, var_name)));
    }
}
void ft_export(char **cmd, t_cmd_inf minish)
{
    int i;
    char *var_name;
    char *var_value;
    
    i = 1;
    var_name = NULL;
    var_value = NULL;
    if (!cmd[1])
        ft_export_print(minish);
    while (cmd[i])
    {
        if (check_alphanum(cmd[i]) == 0)
        {
            ft_putstr_fd("bash: export: '", 2);
            ft_putstr_fd(cmd[i], 2);
            ft_putendl_fd("': not a valid identifier", 2);
        }
        // verify the allocaiton how its made and change it
        var_name = ft_substr(cmd[i], 0, find_value(cmd[i]));
        // seprate func
        int pos = find_value(cmd[i]);
        var_value = ft_substr(cmd[i], pos + 1, ft_strlen(cmd[i]) - pos - 1);
        add_or_replace(pos, minish, var_name, var_value);
        i++;
    }
}