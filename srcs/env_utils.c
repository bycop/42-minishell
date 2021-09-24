/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperrier <jperrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 14:22:34 by sfournio          #+#    #+#             */
/*   Updated: 2021/09/23 14:28:03 by jperrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_key(char *line)
{
	int		i;
	char	*key;

	if (!line || !line[0])
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '=')
		i++;
	key = malloc(sizeof(char) * (i + 1));
	if (key == NULL)
		return (NULL);
	key[0] = '\0';
	ft_memcpy(key, line, i);
	key[i] = '\0';
	return (key);
}

char	*remove_dquote(char *value)
{
	int		len;
	char	*new;

	if (!value)
		return (NULL);
	len = ft_strlen(value);
	if (value[0] == '"' && value[1] == '"')
		return (NULL);
	if (value[0] == '"' && value[len - 1] == '"')
	{
		new = malloc(sizeof(char) * (len - 1));
		if (new == NULL)
			return (NULL);
		ft_memcpy(new, &value[1], len - 2);
		new[len - 2] = '\0';
		return (new);
	}
	return (ft_strdup(value));
}

char	*env_value(char *line)
{
	int		i;
	int		len;
	char	*value;

	if (!line)
		return (NULL);
	i = -1;
	while (line[++i])
		if (i > 0 && line[i - 1] == '=')
			break ;
	if (line[i])
	{
		if (i > 0 && line[i - 1] == '=')
		{
			len = ft_strlen(&line[i]);
			value = malloc(sizeof(char) * (len + 1));
			if (value == NULL)
				return (NULL);
			ft_memcpy(value, &line[i], len);
			value[len] = '\0';
			return (value);
		}
	}
	return (ft_strdup(""));
}

int	env_name_valid(char *line)
{
	int	i;

	i = 0;
	if (line[i] == '=')
		return (-1);
	while (line[i] && line[i] != '=')
	{
		if (!ft_isalnum(line[i]))
			return (-1);
		i++;
	}
	return (0);
}
