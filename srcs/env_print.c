/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperrier <jperrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 14:02:07 by bycop          #+#    #+#             */
/*   Updated: 2021/09/23 15:48:28 by jperrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	env_print_export(int fd, char *line)
{
	char	*name;
	char	*value;

	name = env_key(line);
	value = env_value(line);
	if (value)
		ft_printf(fd, "declare -x %s=\"%s\"\n", name, value);
	else
		ft_printf(fd, "declare -x %s=\"\"\n", name);
	free(name);
	if (value)
		free(value);
}

static int	set_fd(void)
{
	int		fd;

	fd = STDOUT_FILENO;
	if (g_minishell.pipe_out)
	{
		if (pipe(g_minishell.right_pipe) == -1)
			return (ret_error(1));
		fd = g_minishell.right_pipe[1];
	}
	return (fd);
}

static void	reset_fd(void)
{
	if (g_minishell.pipe_out)
		close(g_minishell.right_pipe[1]);
	else
	{
		close(STDOUT_FILENO);
		dup2(g_minishell.fd_output_o, STDOUT_FILENO);
	}
}

void	env_print_alphaorder(int i, int j, char	*last, char *low)
{
	char	*name;
	int		fd;

	fd = set_fd();
	while (j < env_len())
	{
		i = 0;
		low = NULL;
		while (g_minishell.env[i])
		{
			name = env_key(g_minishell.env[i]);
			if ((low == NULL && ft_strcmp_upper(g_minishell.env[i], last) > 0)
				|| (ft_strcmp_upper(last, name) < 0
					&& ft_strcmp_upper(low, name) > 0))
				low = g_minishell.env[i];
			free(name);
			i++;
		}
		env_print_export(fd, low);
		last = low;
		j++;
	}
	reset_fd();
}

void	env_print(int fd)
{
	int		i;
	char	*value;
	char	*name;

	i = 0;
	while (g_minishell.env[i])
	{
		name = env_key(g_minishell.env[i]);
		value = env_value(g_minishell.env[i]);
		if (value)
			ft_printf(fd, "%s=%s\n", name, value);
		else
			ft_printf(fd, "%s=\n", name);
		if (value)
			free(value);
		free(name);
		i++;
	}
}
