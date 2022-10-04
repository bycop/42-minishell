/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bycop <bycop@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 13:46:39 by bycop          #+#    #+#             */
/*   Updated: 2020/11/23 02:14:09 by bycop         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dsize;
	size_t	i;

	dsize = 0;
	i = 0;
	while (dest[dsize] && dsize < size)
		dsize++;
	while (src[i] && i + dsize + 1 < size)
	{
		dest[dsize + i] = src[i];
		i++;
	}
	if (dsize != size)
		dest[dsize + i] = '\0';
	return (dsize + (size_t)ft_strlen(src));
}
