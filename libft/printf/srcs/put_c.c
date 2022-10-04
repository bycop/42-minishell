/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_c.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperrier <jperrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 00:45:26 by bycop          #+#    #+#             */
/*   Updated: 2021/09/16 09:07:08 by jperrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_c(char c, t_minishell infos)
{
	int	i;

	i = -1;
	if (infos.flagm)
	{
		ft_putchar(c);
		while (++i < infos.precision - 1)
			ft_putchar(' ');
		return (i + 1);
	}
	else if (infos.precision > 0 && !infos.flagm)
	{
		while (++i < infos.precision - 1)
			ft_putchar(' ');
		ft_putchar(c);
		return (i + 1);
	}
	return (ft_putchar(c));
}

int	ft_putchar_pourcent(char c, t_minishell infos)
{
	int	i;

	i = -1;
	if (infos.flagm)
	{
		ft_putchar(c);
		while (++i < infos.precision - 1)
			ft_putchar(' ');
		return (i + 1);
	}
	else if (infos.precision > 0 && infos.flagz)
	{
		while (++i < infos.precision - 1)
			ft_putchar('0');
		ft_putchar(c);
		return (i + 1);
	}
	else if (infos.precision > 0 && !infos.flagm)
	{
		while (++i < infos.precision - 1)
			ft_putchar(' ');
		ft_putchar(c);
		return (i + 1);
	}
	return (ft_putchar(c));
}
