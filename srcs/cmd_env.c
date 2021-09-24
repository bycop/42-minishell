/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperrier <jperrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 10:45:08 by sfournio          #+#    #+#             */
/*   Updated: 2021/09/23 15:27:31 by jperrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(t_cmd *cmd)
{
	char	*name;
	char	*value;

	if (cmd->args[1] == NULL)
	{
		env_print_alphaorder(0, 0, NULL, NULL);
		return (set_error(1));
	}
	if (env_name_valid(cmd->args[1]) == -1)
	{
		ft_printf(STDOUT_FILENO, "export: \'%s\': %s\n", cmd->args[1], INV_ID);
		g_minishell.return_value = 1;
		return (set_error(1));
	}
	name = env_key(cmd->args[1]);
	value = env_value(cmd->args[1]);
	if (name != NULL)
	{
		env_set(name, value, 0, NULL);
		free(name);
		if (value != NULL)
			free(value);
	}
}

void	ft_unset(t_cmd *cmd)
{
	env_unset(cmd->args[1], 0, 0, NULL);
}

void	ft_env(t_cmd *cmd)
{
	int	fd;

	cmd->nb_args = cmd->nb_args;
	fd = STDOUT_FILENO;
	if (g_minishell.pipe_out)
	{
		if (pipe(g_minishell.right_pipe) == -1)
			return (set_error(1));
		fd = g_minishell.right_pipe[1];
	}
	env_print(fd);
	if (g_minishell.pipe_out)
		close(g_minishell.right_pipe[1]);
	else
	{
		close(STDOUT_FILENO);
		dup2(g_minishell.fd_output_o, STDOUT_FILENO);
	}
}
