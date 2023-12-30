/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelhaj- <mbelhaj-@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 14:25:09 by mbelhaj-          #+#    #+#             */
/*   Updated: 2023/12/30 14:28:01 by mbelhaj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_cmd(t_cmd_inf *c)
{
	char	*input;
	char	**token;

	input = readline(ANSI_COLOR_GREEN "MyShell$ " ANSI_COLOR_RESET);
	if (input == NULL)
		return (NULL);
	if (input[0] != '\0')
	{
		token = ft_split(input, ' ');
		add_history(input);
		token = history_tokenize(input);
		ft_add_history(input, &c->history, &c->lst);
	}
	rl_replace_line("", 0);
	rl_redisplay();
	c->input = ft_strdup(input);
	free(input);
	return (c->input);
}

void	printf_hst(t_historylist *history)
{
	int				index;
	t_historylist	*current;

	index = 0;
	current = history;
	while (current != NULL)
	{
		printf("%d %s\n", index++, current->command);
		current = current->next;
	}
}

int	ft_check(int c)
{
	if (c == '|')
		return (PIPE);
	else if (c == '>')
		return (GREAT);
	else if (c == '<')
		return (LESS);
	return (0);
}

void	free_split(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
