/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bycop <bycop@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 11:33:41 by jperrier          #+#    #+#             */
/*   Updated: 2021/09/22 11:55:33 by bycop         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	env_unset_end(char **tmp, int j)
{
	tmp[j] = NULL;
	free(g_minishell.env);
	g_minishell.env = tmp;
}

int	env_unset(char *name, int i, int j, char *tname)
{
	char	**tmp;

	if (!env_contains(name))
		return (0);
	tmp = malloc(sizeof(char *) * (env_len() + 1));
	if (!tmp)
		return (-1);
	while (g_minishell.env[i] != NULL)
	{
		tname = env_key(g_minishell.env[i]);
		if (tname != NULL)
		{
			if (ft_strncmp(tname, name, ft_strlen(name) + 1) == 0)
			{
				free(tname);
				free(g_minishell.env[i++]);
				continue ;
			}
			free(tname);
		}
		tmp[j++] = g_minishell.env[i++];
	}
	env_unset_end(tmp, j);
	return (0);
}
