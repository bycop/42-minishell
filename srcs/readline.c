/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bycop <bycop@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 10:51:27 by bycop          #+#    #+#             */
/*   Updated: 2021/09/22 10:51:28 by bycop         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_prompt(void)
{
	if (g_minishell.input_mode)
	{
		g_minishell.prompt = "> ";
	}
	else if (g_minishell.return_value == 0)
		g_minishell.prompt = "\e[92m✔️ \e[93mMinishell\e[94m ⪼ \e[0m";
	else
		g_minishell.prompt = "\e[31m✗ \e[93mMinishell\e[94m ⪼ \e[0m";
}

void	handle_d(void)
{
	if (g_minishell.input_mode)
	{
		g_minishell.input_mode = 0;
		free(g_minishell.delimiter_str);
		g_minishell.delimiter_str = NULL;
		free(g_minishell.delimiter);
		return ;
	}
	ft_printf(1, "exit");
	free_all();
	exit(EXIT_SUCCESS);
}

void	handle_signals(int signo)
{
	if (signo == SIGINT)
	{
		g_minishell.return_value = 1;
		set_prompt();
		ft_printf(1, "\n");
		if (g_minishell.input_mode)
		{
			g_minishell.input_mode = 0;
			set_prompt();
			rl_replace_line("", 0);
			rl_set_prompt(g_minishell.prompt);
			rl_redisplay();
			return ;
		}
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signo == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signo == 404)
		handle_d();
}

void	wait_input(void)
{
	set_prompt();
	g_minishell.original = readline(g_minishell.prompt);
	if (g_minishell.original == NULL)
		handle_signals(404);
	if (g_minishell.original != NULL && g_minishell.input_mode != 1)
		add_history(g_minishell.original);
}
