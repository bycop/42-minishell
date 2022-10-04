/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bycop <bycop@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 13:46:32 by bycop          #+#    #+#             */
/*   Updated: 2021/03/19 10:32:02 by bycop         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	freeall(char **res, int j)
{
	int	i;

	i = -1;
	while (++i <= j)
		free(res[i]);
	free(res);
}

static char	*wordcreate(char c, char const *s)
{
	int		i;
	char	*word;

	i = 0;
	while (s[i] && c != s[i])
		i++;
	word = malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	i = -1;
	while (s[++i] && c != s[i])
		word[i] = s[i];
	word[i] = '\0';
	return (word);
}

static int	countword(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && c == s[i])
			i++;
		if (s[i] && c != s[i])
			count++;
		while (s[i] && c != s[i])
			i++;
	}
	return (count);
}

char	**extend(char **res, int j)
{
	if (res[j - 1] == NULL)
	{
		freeall(res, j - 1);
		return (NULL);
	}
	return (res);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**res;

	i = 0;
	j = 0;
	res = malloc(sizeof(char *) * (countword(s, c) + 1));
	if (!s || !res)
		return (NULL);
	while (s[i])
	{
		while (s[i] && c == s[i])
			i++;
		if (s[i] && c != s[i])
		{
			res[j++] = wordcreate(c, &s[i]);
			if (extend(res, j) == NULL)
				return (NULL);
			while (s[i] && c != s[i])
				i++;
		}
	}
	res[j] = 0;
	return (res);
}
