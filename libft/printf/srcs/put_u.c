/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_u.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperrier <jperrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 00:45:26 by sfournio          #+#    #+#             */
/*   Updated: 2021/09/16 09:07:08 by jperrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	u_len(int nb)
{
	unsigned int	nbr;
	int				i;

	nbr = nb;
	i = 0;
	while (1)
	{
		nbr /= 10;
		i++;
		if (nbr == 0)
			return (i);
	}
}

int	ft_put_u_2(t_minishell infos, int nb, int l, int type)
{
	int	max;

	max = 0;
	if (type == 1)
	{
		while (l++ < infos.precision)
			max += ft_putchar('0');
		max += ft_putnbr_u(nb);
		return (max);
	}
	else if (type == 2)
	{
		while (l++ < infos.precision)
			max += ft_putchar(' ');
		if (nb != 0)
			max += ft_putnbr_u(nb);
		else
			max += ft_putchar(' ');
		return (max);
	}
	while (l++ < infos.flagp)
		max += ft_putchar('0');
	while (l++ <= infos.precision + 1)
		max += ft_putchar(' ');
	return (max);
}

int	ft_put_u_1(t_minishell infos, int nb, int l, int type)
{
	int	max;
	int	i;

	i = -1;
	max = 0;
	if (type == 1)
	{
		while (++i < infos.precision - pointlen(l, infos))
			max += ft_putchar(' ');
		while (l++ < infos.flagp)
			max += ft_putchar('0');
		max += ft_putnbr_u(nb);
	}
	else
	{
		while (l++ < infos.flagp)
			max += ft_putchar('0');
		max += ft_putnbr_u(nb);
		while (l++ <= infos.precision)
			max += ft_putchar(' ');
	}
	return (max);
}

int	ft_put_u(t_minishell infos, va_list va)
{
	int	nb;
	int	l;
	int	print;

	print = 0;
	nb = va_arg(va, int);
	if (nb < 0)
		nb = nb + 4294967296;
	if (nb == 0 && (infos.flagp == 0 && infos.precision <= 0))
		return (0);
	l = u_len(nb);
	if (infos.flagz && (infos.flagp == -1 && !infos.flagm))
		print += ft_put_u_2(infos, nb, l, 1);
	else if (!infos.flagm && infos.flagp == 0 && infos.precision)
		print += ft_put_u_2(infos, nb, l, 2);
	else if (!infos.flagm && (infos.precision >= 0 || infos.flagp >= 0))
		print += ft_put_u_1(infos, nb, l, 1);
	else if (infos.flagm && nb == 0 && infos.flagp == 0)
		print += ft_put_u_2(infos, nb, l, 0);
	else if (infos.flagm)
		print += ft_put_u_1(infos, nb, l, 0);
	else
		print += ft_putnbr_u(nb);
	return (print);
}
