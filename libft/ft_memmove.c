/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournio <sfournio@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 21:32:21 by sfournio          #+#    #+#             */
/*   Updated: 2021/03/19 10:15:45 by sfournio         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!(dst) && !(src))
		return (NULL);
	if ((unsigned char *)dst < (const unsigned char *)src)
	{
		while (n--)
		{
			((unsigned char *)dst)[i] = ((const unsigned char *)src)[i];
			i++;
		}
	}
	else
		while (n--)
			((unsigned char *)dst)[n] = ((const unsigned char *)src)[n];
	return (dst);
}
