/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournio <sfournio@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 10:49:56 by jperrier          #+#    #+#             */
/*   Updated: 2021/03/19 10:32:35 by sfournio         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp_upper(const char *s1, const char *s2)
{
	unsigned int	i;

	if (!s1 && !s2)
		return (0);
	if (s1 && !s2)
		return (1);
	if (!s1 && s2)
		return (-1);
	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (ft_toupper(s1[i]) - ft_toupper(s2[i]) != 0)
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
