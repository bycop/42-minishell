/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperrier <jperrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 11:33:01 by sfournio          #+#    #+#             */
/*   Updated: 2021/09/22 11:25:19 by jperrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main_inputmode(void)
{
	if (ft_strncmp(g_minishell.original, g_minishell.delimiter,
			ft_strlen(g_minishell.delimiter) + 1) == 0)
	{
		write(g_minishell.delimiter_pipes[1], g_minishell.delimiter_str,
			ft_strlen(g_minishell.delimiter_str));
		close(g_minishell.delimiter_pipes[1]);
		close(g_minishell.delimiter_pipes[0]);
		g_minishell.input_mode = 0;
		free(g_minishell.delimiter_str);
		g_minishell.delimiter_str = NULL;
		free(g_minishell.delimiter);
	}
	else
	{
		g_minishell.delimiter_str = ft_strjoinfree(
				g_minishell.delimiter_str, g_minishell.original, 1);
		g_minishell.delimiter_str = ft_strjoinfree(
				g_minishell.delimiter_str, "\n", 1);
	}
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	ac = 0;
	av = NULL;
	if (signal(SIGINT, handle_signals) == SIG_ERR
		|| signal(SIGQUIT, handle_signals) == SIG_ERR)
	{
		ft_printf(g_minishell.fd_output, "%s\n", KERNEL_REGISTER);
	}
	if (init_minishell(envp))
		exit(EXIT_FAILURE);
	while (1)
	{
		if (reset_minishell())
			break ;
		wait_input();
		if (g_minishell.input_mode && main_inputmode())
			continue ;
		extract_paths();
		if (g_minishell.original == NULL || !check_space(g_minishell.original))
			continue ;
		parse_line();
		process_tokens();
		free_loop();
	}
	return (0);
}
