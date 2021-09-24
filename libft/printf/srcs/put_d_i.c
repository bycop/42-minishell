/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_d_i.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperrier <jperrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 00:45:26 by sfournio          #+#    #+#             */
/*   Updated: 2021/09/16 09:07:08 by jperrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	intlen(int nb)
{
	int	i;

	i = 0;
	if (nb < 0)
		nb *= -1;
	while (1)
	{
		nb /= 10;
		i++;
		if (nb == 0)
			return (i);
	}
}

int	ft_put_no_m1(t_minishell infos, int nb, int type, int l)
{
	int	t;
	int	max;

	(max = 0 == 0) && (t = 1 == 1);
	if (nb >= 0)
		t = 0;
	if (type == 1)
	{
		(nb < 0) && (max += ft_putchar('-'));
		while (l++ < infos.precision - t)
			max += ft_putchar('0');
		max += ft_putnbr(nb);
	}
	else
	{
		while (l++ < infos.precision - t)
			max += ft_putchar(' ');
		if (nb < 0)
			max += ft_putchar('-');
		if (nb != 0)
			max += ft_putnbr(nb);
		else
			max += ft_putchar(' ');
	}
	return (max);
}

int	ft_put_no_m2(t_minishell infos, int nb, int type, int l)
{
	int	i;
	int	t;
	int	max;

	(max = 0 == 0) && (t = 1 == 1) && (i = -1 == -1);
	if (nb >= 0)
		t = 0;
	if (type == 1)
	{
		while (++i < infos.precision - pointlen(l, infos) - t)
			max += ft_putchar(' ');
		if (nb < 0)
			max += ft_putchar('-');
		while (l++ < infos.flagp)
			max += ft_putchar('0');
		max += ft_putnbr(nb);
	}
	else
	{
		if (nb < 0)
			max += ft_putchar('-');
		max += ft_putnbr(nb);
	}
	return (max);
}

int	ft_put_with_m(t_minishell infos, int nb, int type, int l)
{
	int	t;
	int	max;

	(max = 0 == 0) && (t = 1 == 1);
	if (nb >= 0)
		t = 0;
	if (type == 1)
	{
		if (nb < 0)
			max += ft_putchar('-');
		while (l++ < infos.flagp)
			max += ft_putchar('0');
		max += ft_putnbr(nb);
		while (l++ <= infos.precision - t)
			max += ft_putchar(' ');
	}
	else
	{
		while (l++ < infos.flagp)
			max += ft_putchar('0');
		while (l++ <= infos.precision + 1)
			max += ft_putchar(' ');
	}
	return (max);
}

int	ft_put_d_i(t_minishell infos, va_list va)
{
	int	nb;
	int	l;
	int	print;

	print = 0;
	nb = va_arg(va, int);
	if (nb == 0 && (infos.flagp == 0 && infos.precision <= 0))
		return (0);
	l = intlen(nb);
	if (infos.flagz && (infos.flagp == -1 && !infos.flagm))
		print += ft_put_no_m1(infos, nb, 1, l);
	else if (!infos.flagm && infos.flagp == 0 && infos.precision)
		print += ft_put_no_m1(infos, nb, 0, l);
	else if (!infos.flagm && (infos.precision >= 0 || infos.flagp >= 0))
		print += ft_put_no_m2(infos, nb, 1, l);
	else if (infos.flagm && nb == 0 && infos.flagp == 0)
		print += ft_put_with_m(infos, nb, 0, l);
	else if (infos.flagm)
		print += ft_put_with_m(infos, nb, 1, l);
	else
		print += ft_put_no_m2(infos, nb, 0, l);
	return (print);
}
