/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flafi <flafi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 02:11:45 by flafi             #+#    #+#             */
/*   Updated: 2023/12/28 02:12:37 by flafi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// change it later to ft malloc for leaks
t_list	*fill_envlst(char **envp)
{
	int		i;
	t_list	*envlst;

	i = 1;
	envlst = ft_lstnew(envp[0]);
	// printf("content of the first lst = %s\n", envlst->content);
	while (envp[i])
	{
		ft_lstadd_back(&envlst, ft_lstnew(envp[i]));
		i++;
	}
	return (envlst);
}

void	ft_init_envp(t_cmd_inf *c, char **envp)
{
	c->env = envp;
	c->envlst = fill_envlst(envp);
	c->exp_flag = 0;
	c->rtn_code = 0;
	c->history = NULL;
	c->lst = NULL;
}
void	signal_interrupt(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		exit(EXIT_SUCCESS);
}
void	sigs(void)
{
	// rl_catch_signals = 0;
	g_sign.sa_handler = signal_interrupt;
	g_sign.sa_flags = 0;
	sigaction(SIGINT, &g_sign, NULL);
	sigaction(SIGQUIT, &g_sign, NULL);
	// rl_clear_signals();
}