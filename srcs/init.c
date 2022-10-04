/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperrier <jperrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 13:05:59 by bycop          #+#    #+#             */
/*   Updated: 2021/09/23 14:39:25 by jperrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_minishell(char **envp)
{
	char	*key;

	env_init(envp);
	key = env_get("SHLVL", 0, NULL, NULL);
	if (key)
	{
		key = ft_itoa(ft_atoi(key) + 1);
		env_set("SHLVL", key, 0, NULL);
		free(key);
	}
	key = getcwd(NULL, 1000);
	key = ft_strjoinfree(key, "/minishell", 1);
	env_set("SHELL", key, 0, NULL);
	free(key);
	g_minishell.return_value = 0;
	g_minishell.fd_input_o = dup(STDIN_FILENO);
	g_minishell.fd_output_o = dup(STDOUT_FILENO);
	g_minishell.fd_input = dup(STDIN_FILENO);
	g_minishell.fd_output = dup(STDOUT_FILENO);
	g_minishell.original = NULL;
	g_minishell.input_mode = 0;
	g_minishell.cmd_token = NULL;
	g_minishell.delimiter = NULL;
	g_minishell.delimiter_str = NULL;
	return (0);
}

int	reset_minishell(void)
{
	g_minishell.tokens = NULL;
	g_minishell.cmd_token = NULL;
	g_minishell.original = NULL;
	if (g_minishell.delimiter_str == NULL)
	{
		g_minishell.delimiter_str = malloc(1);
		if (!g_minishell.delimiter_str)
			return (1);
		g_minishell.delimiter_str[0] = '\0';
	}
	return (0);
}
