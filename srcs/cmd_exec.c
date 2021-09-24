/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournio <sfournio@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 10:45:26 by sfournio          #+#    #+#             */
/*   Updated: 2021/09/23 15:37:14 by sfournio         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_cmd *cmd)
{
	int		old_slash;
	char	old_pwd[1000];

	getcwd(old_pwd, 1000);
	old_slash = g_minishell.double_slash;
	g_minishell.double_slash = -1;
	g_minishell.return_value = ft_cd_main(cmd);
	if (g_minishell.double_slash == -1)
		g_minishell.double_slash = old_slash;
	if (g_minishell.return_value == 0)
	{
		if (old_slash == 1)
			env_set("OLDPWD", ft_strjoin("/", old_pwd), 0, NULL);
		else
			env_set("OLDPWD", old_pwd, 0, NULL);
	}
}

void	ft_pwd(t_cmd *cmd)
{
	char	buf[1000];
	int		fd;

	cmd->nb_args = cmd->nb_args;
	fd = STDOUT_FILENO;
	if (g_minishell.pipe_out)
	{
		if (pipe(g_minishell.right_pipe) == -1)
			return ;
		fd = g_minishell.right_pipe[1];
	}
	getcwd(buf, 1000);
	if (g_minishell.double_slash == 1)
		ft_printf(fd, "/");
	ft_printf(fd, "%s\n", buf);
	g_minishell.return_value = 0;
	if (g_minishell.pipe_out)
		close(g_minishell.right_pipe[1]);
	else
	{
		close(STDOUT_FILENO);
		dup2(g_minishell.fd_output_o, STDOUT_FILENO);
	}
}

void	ft_path(t_cmd *cmd)
{
	int	found;

	found = found_cmd(cmd, 0, 0);
	if (found == 2)
	{
		g_minishell.return_value = 127;
		ft_printf(1, "\e[91m%s: \e[0m%s: %s\n", EXEC_NAME, cmd->args[0],
			ENOENT_ERR);
	}
	else if (found == 3)
	{
		g_minishell.return_value = 126;
		ft_printf(1, "\e[91m%s: \e[0m%s: %s\n", EXEC_NAME, cmd->args[0],
			IS_DIR);
	}
	else if (!found)
	{
		g_minishell.return_value = 127;
		ft_printf(1, "\e[91m%s: \e[0m%s: %s\n", EXEC_NAME, cmd->args[0],
			CMD_NOTFOUND);
	}
}

void	run_cmd(t_cmd *cmd, void (*functions[7])(t_cmd *), int *found, int i)
{
	functions[i](cmd);
	*found = 1;
}

void	find_cmd(t_cmd *cmd, int i, int found, char *lower)
{
	static char		*c[7] = {"echo", "cd", "pwd", "export",
		"unset", "env", "exit"};
	static void		(*functions[7])(t_cmd *) = {&ft_echo, &ft_cd, &ft_pwd,
		&ft_export, &ft_unset, &ft_env, &ft_exit};

	while (++i < 7 && found == 0)
	{
		if (i < 3)
		{
			lower = str_tolower(cmd->args[0]);
			if (ft_strncmp(lower, c[i], ft_strlen(c[i]) + 1) == 0)
				run_cmd(cmd, functions, &found, i);
			free(lower);
		}
		else if (ft_strncmp(cmd->args[0], c[i], ft_strlen(c[i]) + 1) == 0)
			run_cmd(cmd, functions, &found, i);
	}
	if (!found)
		ft_path(cmd);
}
