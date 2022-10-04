/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperrier <jperrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 13:06:11 by bycop          #+#    #+#             */
/*   Updated: 2021/09/22 11:35:20 by jperrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	next_space(char *s, int type)
{
	int	i;

	i = -1;
	if (type == 2)
	{
		while (s[++i])
			if (!ft_isalnum(s[i]) && s[i] != '?')
				return (i);
	}
	else
	{
		while (s[++i])
			if (!ft_isalnum(s[i]))
				return (i);
	}
	return (i);
}

int	skip_space(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] == ' ')
		i++;
	return (i);
}

int	check_space(char *input)
{
	int	i;

	i = -1;
	while (++i < (int)ft_strlen(input))
		if (input[i] != ' ')
			return (1);
	free(input);
	return (0);
}
