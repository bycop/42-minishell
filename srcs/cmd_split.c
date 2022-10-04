/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperrier <jperrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 10:55:20 by bycop          #+#    #+#             */
/*   Updated: 2021/09/22 11:26:41 by jperrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(char *s)
{
	int	i;
	int	count;
	int	sq;
	int	dq;

	i = skip_space(s);
	count = 0;
	sq = -1;
	dq = -1;
	while (s[i] != '\0')
	{
		if (s[i] == '\'' && (!s[i - 1] || s[i - 1] != '\\'))
			sq *= -1;
		else if (s[i] == '"' && (!s[i - 1] || s[i - 1] != '\\'))
			dq *= -1;
		else if (s[i] == ' ' && sq < 0 && dq < 0)
		{
			while (s[i + 1] && s[i + 1] == ' ')
				i++;
			if (s[i + 1])
				count++;
		}
		i++;
	}
	return (count + 1);
}

char	*create_args(char *s, int *i)
{
	int		sq;
	int		dq;
	char	*res;

	sq = -1;
	dq = -1;
	res = ft_strdup("");
	while (s[*i] != '\0')
	{
		if (s[*i] == '\'' && (!s[*i - 1] || s[*i - 1] != '\\'))
			sq *= -1;
		if (s[*i] == '"' && (!s[*i - 1] || s[*i - 1] != '\\'))
			dq *= -1;
		if (s[*i] == ' ' && dq < 0 && sq < 0)
			return (res);
		res = ft_strljoinfree(res, s + *i, 1);
		*i += 1;
	}
	return (res);
}

char	**split_args(t_cmd *cmd, char *str)
{
	char	**args;
	int		nb_args;
	int		i;
	int		index;

	i = -1;
	index = 0;
	nb_args = count_args(str);
	cmd->nb_args = nb_args;
	args = malloc((nb_args + 1) * sizeof(char *));
	if (args == NULL)
		return (NULL);
	while (++i < nb_args)
	{
		index += skip_space(str + index);
		args[i] = create_args(str, &index);
	}
	args[i] = NULL;
	cmd->args = args;
	return (NULL);
}
