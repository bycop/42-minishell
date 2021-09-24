/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperrier <jperrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 11:07:32 by jperrier          #+#    #+#             */
/*   Updated: 2021/09/23 13:00:06 by jperrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	path_child(char *command, char **cmd)
{
	if (g_minishell.pipe_in)
	{
		close(g_minishell.left_pipe[1]);
		dup2(g_minishell.left_pipe[0], STDIN_FILENO);
	}
	if (g_minishell.pipe_out)
	{
		close(g_minishell.right_pipe[0]);
		dup2(g_minishell.right_pipe[1], STDOUT_FILENO);
	}
	if (g_minishell.input_mode)
	{
		close(g_minishell.delimiter_pipes[1]);
		dup2(g_minishell.delimiter_pipes[0], STDIN_FILENO);
	}
	execve(command, cmd, g_minishell.env);
	if (g_minishell.pipe_out)
	{
		close(STDOUT_FILENO);
		close(g_minishell.right_pipe[1]);
	}
}

void	path_parent(pid_t pid, int status)
{
	if (g_minishell.pipe_in)
	{
		close(g_minishell.left_pipe[0]);
		dup2(g_minishell.left_pipe[0], STDIN_FILENO);
	}
	if (g_minishell.pipe_out)
	{
		close(g_minishell.right_pipe[1]);
	}
	if (g_minishell.input_mode)
		close(g_minishell.delimiter_pipes[0]);
	else
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
		if (WIFEXITED(status))
			g_minishell.return_value = WEXITSTATUS(status);
	}
	if (!g_minishell.pipe_out)
		dup2(g_minishell.fd_output_o, STDOUT_FILENO);
	dup2(g_minishell.fd_input_o, STDIN_FILENO);
}
