/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bycop <bycop@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 18:33:22 by bycop          #+#    #+#             */
/*   Updated: 2020/11/23 02:13:23 by bycop         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int ch, size_t n)
{
	size_t	i;

	i = -1;
	while (++i < n)
		if (((unsigned const char *)str)[i] == (unsigned char)ch)
			return (((unsigned char *)str) + i);
	return (NULL);
}
