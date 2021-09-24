/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperrier <jperrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 10:30:28 by sfournio          #+#    #+#             */
/*   Updated: 2021/09/23 15:47:18 by jperrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_n(char *str)
{
	int	i;

	i = 0;
	if (ft_strncmp(str, "-n", 3) == 0)
		return (1);
	if (str[i++] != '-')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static void	echo_in(t_cmd *cmd, int fd)
{
	int	i;

	i = 1;
	while (i < cmd->nb_args && is_n(cmd->args[i]))
		i++;
	while (i < cmd->nb_args)
	{
		ft_printf(fd, "%s", cmd->args[i]);
		if (i != cmd->nb_args - 1)
			ft_printf(fd, " ");
		i++;
	}
	if (!cmd->args[1] || !is_n(cmd->args[1]))
		ft_printf(fd, "\n");
}

void	ft_echo(t_cmd *cmd)
{
	int	fd;

	fd = STDOUT_FILENO;
	if (g_minishell.pipe_out)
	{
		if (pipe(g_minishell.right_pipe) == -1)
			return ;
		fd = g_minishell.right_pipe[1];
	}
	echo_in(cmd, fd);
	g_minishell.return_value = 0;
	if (g_minishell.pipe_out)
		close(g_minishell.right_pipe[1]);
	else
	{
		close(STDOUT_FILENO);
		dup2(g_minishell.fd_output_o, STDOUT_FILENO);
	}
}
