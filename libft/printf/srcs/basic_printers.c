/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_printers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournio <sfournio@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 07:14:43 by sfournio          #+#    #+#             */
/*   Updated: 2021/04/01 12:57:41 by sfournio         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putnbr(int n)
{
	long	nb;
	int		i;
	int		save;
	char	c[10];

	nb = n;
	if (nb == 0)
		return (ft_putchar('0'));
	if (nb < 0)
		nb = -nb;
	i = 0;
	while (nb > 0)
	{
		c[i] = nb % 10 + '0';
		nb = nb / 10;
		i++;
	}
	save = i;
	while (--i >= 0)
		ft_putchar(c[i]);
	return (save);
}

int	ft_putnbr_u(int n)
{
	unsigned int	nb;
	int				i;
	int				save;
	char			c[10];

	nb = n;
	if (nb == 0)
		return (ft_putchar('0'));
	i = 0;
	while (nb > 0)
	{
		c[i] = nb % 10 + '0';
		nb = nb / 10;
		i++;
	}
	save = i;
	while (--i >= 0)
		ft_putchar(c[i]);
	return (save);
}

int	ft_putstr(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		ft_putchar(s[i]);
	return (i);
}
