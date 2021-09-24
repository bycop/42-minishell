/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperrier <jperrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 08:52:42 by sfournio          #+#    #+#             */
/*   Updated: 2021/09/16 09:07:08 by jperrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_tolow(char *s)
{
	int	i;

	if (s == NULL)
		return (NULL);
	i = -1;
	while (s[++i])
		if (s[i] >= 'A' && s[i] <= 'Z')
			s[i] += 32;
	return (s);
}

char	*ft_strrev(char *src)
{
	int		length;
	int		i;
	char	temp;

	length = ft_strlen(src);
	i = -1;
	while (++i < length / 2)
	{
		temp = src[i];
		src[i] = src[length - i - 1];
		src[length - i - 1] = temp;
	}
	return (src);
}

int	pointlen(int j, t_minishell infos)
{
	if (infos.flagp > -1)
	{
		if (infos.flagp == 0)
			return (0);
		else
		{
			if (infos.flagp >= j)
				return (infos.flagp);
			return (j);
		}
	}
	else
		return (j);
}

char	*little(char *nbr, int i, int *ind)
{
	nbr[i] = '\0';
	*ind += i;
	return (nbr);
}

t_minishell	little2(t_minishell infos)
{
	infos.flagp = 0;
	return (infos);
}
