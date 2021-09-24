/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournio <sfournio@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 18:56:48 by sfournio          #+#    #+#             */
/*   Updated: 2021/04/01 12:53:02 by sfournio         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_charset(char const *set, char c)
{
	int	i;

	i = -1;
	while (set[++i])
		if (c == set[i])
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	int		i;
	int		j;
	int		len;

	if (!s1)
		return (NULL);
	i = 0;
	len = ft_strlen((char *)s1);
	while (is_charset(set, ((char *)s1)[i]))
		if (((char *)s1)[++i] == 0)
			return ((char *)ft_calloc(1, sizeof(char)));
	while (is_charset(set, ((char *)s1)[len - 1]))
		len--;
	len = len - i;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	j = -1;
	while (j++ < len)
		res[j] = s1[i + j];
	res[len] = '\0';
	return (res);
}
