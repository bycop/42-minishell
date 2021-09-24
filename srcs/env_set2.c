/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperrier <jperrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 11:18:48 by jperrier          #+#    #+#             */
/*   Updated: 2021/09/23 14:28:26 by jperrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_contains(char *name)
{
	int		i;
	char	*key;

	i = 0;
	while (g_minishell.env[i] != NULL)
	{
		key = env_key(g_minishell.env[i]);
		if (key != NULL)
		{
			if (ft_strncmp(key, name, ft_strlen(key) + 1) == 0)
			{	
				free(key);
				return (i);
			}
			free(key);
		}
		i++;
	}
	return (-1);
}

char	*env_get(char *name, int i, char *key, char *pwd)
{
	if (ft_strncmp("?", name, 2) == 0)
		return (ft_itoa(g_minishell.return_value));
	if (ft_strncmp("PWD", name, 4) == 0)
	{
		pwd = getcwd(NULL, 1000);
		if (g_minishell.double_slash == 1)
			return (ft_strjoin("/", pwd));
		return (pwd);
	}
	if (ft_isdigit(name[0]) && ft_strlen(name) > 1)
		return (ft_strdup(name + 1));
	while (g_minishell.env[i] != NULL)
	{
		key = env_key(g_minishell.env[i]);
		if (key != NULL)
		{
			if (ft_strncmp(key, name, ft_strlen(key) + 1) == 0)
			{
				return (env_value(g_minishell.env[i]));
			}
			free(key);
		}
		i++;
	}
	return (ft_strdup(""));
}
