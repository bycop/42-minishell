/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperrier <jperrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 10:29:24 by bycop          #+#    #+#             */
/*   Updated: 2021/09/22 11:28:48 by jperrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_errors(int err, t_cmd *cmd)
{
	if (err == ENOENT)
		ft_printf(2, "\e[91m%s: \e[0mcd: %s: %s\n",
			EXEC_NAME, cmd->args[1], ENOENT_ERR);
	if (err == ENOTDIR)
		ft_printf(2, "\e[91m%s: \e[0mcd: %s: %s\n",
			EXEC_NAME, cmd->args[1], ENOTDIR_ERR);
	if (err == OLDPWD_CODE)
		ft_printf(2, "\e[91m%s: \e[0mcd: %s\n", EXEC_NAME, OLDPWD_ERR);
	if (err == EACCES)
		ft_printf(2, "\e[91m%s: \e[0mcd: %s\n", EXEC_NAME, EACCES_ERR);
	return (1);
}

int	simple_path(char *buf2, char *buf, t_cmd *cmd)
{
	if (cmd->args[1][0] == '.' && cmd->args[1][1] == '/')
		buf2 = ft_strjoin("/", cmd->args[1] + 2);
	else
		buf2 = ft_strjoin("/", cmd->args[1]);
	ft_strlcpy(buf + ft_strlen(buf), buf2, ft_strlen(buf2) + 1);
	free(buf2);
	if (chdir(buf) == -1)
		return (cd_errors(errno, cmd));
	return (0);
}

int	ft_cd_main_bis(t_cmd *cmd)
{
	char	buf[1000];
	char	*buf2;

	buf2 = NULL;
	getcwd(buf, 1000);
	if (cmd->args[1][0] == '-' && !cmd->args[1][1])
	{
		if (chdir(env_get("OLDPWD", 0, NULL, NULL)) == -1)
			return (cd_errors(OLDPWD_CODE, cmd));
		if (env_get("OLDPWD", 0, NULL, NULL)[1] == '/')
			g_minishell.double_slash = 1;
		else
			g_minishell.double_slash = 0;
	}
	else if (cmd->args[1][0] == '.' && cmd->args[1][1] == '.')
		return (fictif_main(buf, buf2, cmd));
	else
		return (simple_path(buf2, buf, cmd));
	return (0);
}

int	ft_cd_main(t_cmd *cmd)
{
	if (cmd->args[1] && cmd->args[1][0] == '.'
		&& !cmd->args[1][1])
		return (0);
	if (!cmd->args[1])
	{
		if (chdir(env_get("HOME", 0, NULL, NULL)) == -1)
			return (cd_errors(errno, cmd));
		g_minishell.double_slash = 0;
	}
	else if (cmd->args[1][0] == '/')
	{
		if (chdir(cmd->args[1]) == -1)
			return (cd_errors(errno, cmd));
		if (cmd->args[1][1] == '/')
			g_minishell.double_slash = 1;
		else
			g_minishell.double_slash = 0;
	}
	else
		return (ft_cd_main_bis(cmd));
	return (0);
}
