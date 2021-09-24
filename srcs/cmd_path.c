/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperrier <jperrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 10:53:34 by sfournio          #+#    #+#             */
/*   Updated: 2021/09/23 15:45:38 by jperrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd(char *command, char **cmd)
{
	pid_t	pid;
	int		status;

	if (g_minishell.pipe_out)
	{
		if (pipe(g_minishell.right_pipe) == -1)
			return (1);
	}
	status = 0;
	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid > 0)
	{
		path_parent(pid, status);
	}
	else
	{
		path_child(command, cmd);
		return (1);
	}
	return (0);
}

int	run_path_cmd(t_cmd *cmd, char *command, int *found)
{
	*found = 1;
	return (exec_cmd(command, cmd->args));
}

int	check_valid(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != '.' && str[i] != '/')
			return (1);
	}
	return (0);
}

int	found_cmd(t_cmd *cmd, int found, int j)
{
	struct stat	sb;
	char		*command;
	char		*param;

	if (!stat(cmd->args[0], &sb) && !S_ISDIR(sb.st_mode)
		&& (cmd->args[0][0] == '/' || cmd->args[0][0] == '.'))
		run_path_cmd(cmd, cmd->args[0], &found);
	else if (S_ISDIR(sb.st_mode))
		return (3);
	else if (cmd->args[0][0] != '.' && cmd->args[0][1] != '/')
	{
		param = ft_strjoin("/", cmd->args[0]);
		while (g_minishell.paths[j] && found == 0)
		{
			command = ft_strjoin(g_minishell.paths[j], param);
			if (stat(command, &sb) == 0)
				run_path_cmd(cmd, command, &found);
			free(command);
			j++;
		}
		free(param);
	}
	else
		return (2);
	return (found);
}

void	extract_paths(void)
{
	char	*name;
	char	*value;
	int		i;

	i = 0;
	while (i < env_len())
	{
		name = env_key(g_minishell.env[i]);
		value = env_value(g_minishell.env[i]);
		if (name && ft_strncmp("PATH", name, ft_strlen("PATH")) == 0)
		{
			if (g_minishell.paths)
				strs_free(g_minishell.paths);
			g_minishell.paths = ft_split(value, ':');
			free(value);
			free(name);
			return ;
		}
		if (name)
			free(name);
		if (value)
			free(value);
		i++;
	}
}
