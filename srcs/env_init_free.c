/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bycop <bycop@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 14:08:31 by bycop          #+#    #+#             */
/*   Updated: 2021/09/20 14:13:18 by bycop         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_free(void)
{
	int	i;

	i = 0;
	while (g_minishell.env[i] != NULL)
		free(g_minishell.env[i++]);
	if (g_minishell.env)
		free(g_minishell.env);
	return (0);
}

int	env_init(char **envp)
{
	int		i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	g_minishell.env = malloc(sizeof(char *) * (i + 1));
	if (g_minishell.env == NULL)
		return (-1);
	i = 0;
	while (envp[i] != NULL)
	{
		g_minishell.env[i] = 0;
		g_minishell.env[i] = ft_strdup(envp[i]);
		if (g_minishell.env[i] == NULL)
			return (env_free());
		i++;
	}
	g_minishell.env[i] = NULL;
	env_unset("OLDPWD", 0, 0, NULL);
	return (0);
}
