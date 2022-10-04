/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperrier <jperrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 14:05:59 by bycop          #+#    #+#             */
/*   Updated: 2021/09/22 11:34:41 by jperrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_len(void)
{
	int		i;

	i = 0;
	while (g_minishell.env[i])
		i++;
	return (i);
}

static void	env_set2(char *n, char *v)
{
	free(n);
	free(v);
	free(g_minishell.env);
}

static void	env_set3(char **tmp, char *final, int i)
{
	tmp[i] = final;
	tmp[i + 1] = NULL;
	g_minishell.env = tmp;
}

int	env_set(char *name, char *value, int i, char *v)
{
	char	**tmp;
	char	*n;
	char	*final;

	if (env_contains(name))
		if (env_unset(name, 0, 0, NULL) == -1)
			return (-1);
	tmp = malloc(sizeof(char *) * (env_len() + 2));
	if (tmp == NULL)
		return (-1);
	while (i < env_len())
	{
		tmp[i] = g_minishell.env[i];
		i++;
	}
	n = ft_strjoin(name, "=");
	v = remove_dquote(value);
	if (v == NULL)
		final = ft_strdup(n);
	else
		final = ft_strjoin(n, v);
	env_set2(n, v);
	env_set3(tmp, final, i);
	return (0);
}
