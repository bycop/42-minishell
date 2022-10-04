/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsjoin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bycop <bycop@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 11:33:19 by bycop          #+#    #+#             */
/*   Updated: 2021/07/24 11:33:20 by bycop         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strslen(char **strs)
{
	int	i;

	i = 0;
	if (!strs)
		return (0);
	while (strs[i] != NULL)
		i++;
	return (i);
}

static void	free_all_strs(char **strs, int j)
{
	int	i;

	i = 0;
	while (i != j)
		free(strs[i++]);
	free(strs);
}

char	**ft_strsjoin(char **s1, char *s2)
{
	char	**strs;
	int		i;

	i = 0;
	strs = malloc(sizeof(char *) * (ft_strslen(s1) + 2));
	if (!strs)
		return (NULL);
	if (s1)
	{
		while (s1[i])
		{
			strs[i] = ft_strdup(s1[i]);
			i++;
		}
	}
	strs[i++] = ft_strdup(s2);
	strs[i] = NULL;
	free_all_strs(s1, ft_strslen(s1));
	free(s2);
	return (strs);
}

char	**ft_strsjoin_nofree(char **s1, char *s2)
{
	char	**strs;
	int		i;

	i = 0;
	strs = malloc(sizeof(char *) * (ft_strslen(s1) + 2));
	if (!strs)
		return (NULL);
	if (s1)
	{
		while (s1[i])
		{
			strs[i] = ft_strdup(s1[i]);
			i++;
		}
	}
	strs[i++] = ft_strdup(s2);
	strs[i] = NULL;
	return (strs);
}
