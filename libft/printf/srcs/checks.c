/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperrier <jperrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 23:21:46 by sfournio          #+#    #+#             */
/*   Updated: 2021/09/16 09:07:08 by jperrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_minishell	extens(long int prec, t_minishell infos, int *ind, int type)
{
	if (type == 1)
	{
		*ind += 1;
		if (prec >= 0)
			infos.flagp = prec;
	}
	else
	{
		if (prec < 0)
		{
			infos.precision = -prec;
			infos.flagm = 1;
		}
		else
			infos.precision = prec;
	}
	return (infos);
}

t_minishell	flagpnbr(const char *str, t_minishell infos, int *ind, va_list va)
{
	int			i;
	char		*nbr;

	if (str[0] == '*')
		return (extens(va_arg(va, int), infos, ind, 1));
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (i > 0)
	{
		nbr = malloc(sizeof(char) * (i + 1));
		if (!nbr)
			return (infos);
	}
	else if (i == 0)
	{
		return (little2(infos));
	}
	i = -1;
	while (str[++i] >= '0' && str[i] <= '9')
		nbr[i] = str[i];
	little(nbr, i, ind);
	infos.flagp = ft_atoi(nbr);
	free(nbr);
	return (infos);
}

t_minishell	check_prec(const char *str, t_minishell infos, int *ind, va_list va)
{
	int		i;
	char	*nbr;

	if (str[0] == '*')
		return (extens(va_arg(va, int), infos, ind, 0));
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (i > 0)
	{
		nbr = malloc(sizeof(char) * (i + 1));
		if (!nbr)
			return (infos);
	}
	else
		return (infos);
	i = -1;
	while (str[++i] >= '0' && str[i] <= '9')
		nbr[i] = str[i];
	nbr[i] = '\0';
	infos.precision = ft_atoi(nbr);
	free(nbr);
	*ind += i - 1;
	return (infos);
}

t_minishell	check_flags(const char *str, t_minishell infos, int *ind, va_list va)
{
	int	i;

	i = 0;
	while ((str[i] >= '0' && str[i] <= '9') || str[i] == '-' || str[i] == '.'
		|| str[i] == '*')
	{
		if (str[i] == '0' && i == 0)
			infos.flagz = 1;
		else if (str[i] == '-')
			infos.flagm = 1;
		else if (str[i] == '.')
			infos = flagpnbr(&str[i + 1], infos, &i, va);
		else if ((((str[i] > '0' && str[i] <= '9') || str[i] == '*')
				&& str[i - 1] != '.'))
			infos = check_prec(&str[i], infos, &i, va);
		i++;
	}
	*ind += i;
	return (infos);
}

int	check_type(const char *str, t_minishell infos, va_list va, int *ind)
{
	*ind += 1;
	if (str[0] == 'd' || str[0] == 'i')
		return (ft_put_d_i(infos, va));
	if (str[0] == 'c')
		return (ft_putchar_c(va_arg(va, int), infos));
	if (str[0] == 's')
		return (ft_putstr_prec(va_arg(va, char *), infos));
	if (str[0] == 'u')
		return (ft_put_u(infos, va));
	if (str[0] == 'p')
		return (f_p(ft_tolow(ft_itoa_b_a(va_arg(va, intptr_t), infos)), infos));
	if (str[0] == 'x')
		return (ft_putstr_hex(ft_tolow(ft_itoa_base(va_arg(va, int))), infos));
	if (str[0] == 'X')
		return (ft_putstr_hex(ft_itoa_base(va_arg(va, int)), infos));
	if (str[0] == '%')
		return (ft_putchar_pourcent('%', infos));
	return (0);
}
