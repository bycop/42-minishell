/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperrier <jperrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 11:33:23 by bycop          #+#    #+#             */
/*   Updated: 2021/08/24 12:13:38 by jperrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_type(char c)
{
	if (c == '"')
		return (1);
	else if (c == '\'')
		return (2);
	else
		return (0);
}

int	sep_type(char c, char next)
{
	if (!c)
		return (6);
	else if (c == ';')
		return (1);
	else if (c == '|')
		return (2);
	else if (c == '>' && (!next || next != '>'))
		return (3);
	else if (c == '>' && (next && next == '>'))
		return (4);
	else if (c == '<')
		return (5);
	else
		return (0);
}

char	*found_slash(char *buf2, char *buf, int *i)
{
	while (buf[*i] != '/' && *i != 0)
		*i -= 1;
	if (*i != 0)
		buf2 = ft_substr(buf, 0, *i);
	else
		buf2 = ft_strdup("/");
	if (*i != 0)
		*i -= 1;
	return (buf2);
}

char	*str_tolower(char *str)
{
	char	*res;
	int		i;

	res = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		res[i] = ft_tolower(str[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}

void	strs_free(char **strs)
{
	int		i;

	i = -1;
	while (strs[++i] != NULL)
		free(strs[i]);
	if (strs != NULL)
		free(strs);
}
