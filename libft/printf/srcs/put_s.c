/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_s.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperrier <jperrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 03:16:51 by bycop          #+#    #+#             */
/*   Updated: 2021/09/16 09:07:08 by jperrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	slen(char *s, t_minishell infos)
{
	int	j;

	j = ft_strlen(s);
	if (infos.flagp > -1)
	{
		if (infos.flagp == 0)
			return (0);
		else
		{
			if (infos.flagp >= j)
				return (j);
			return (infos.flagp);
		}
	}
	else
		return (j);
}

int	put_s(char *s, t_minishell infos, int l, int type)
{
	int	i;

	i = -1;
	if (type == 1)
	{
		while (l++ < infos.precision)
			ft_putchar(' ');
		while (s[++i] && (infos.flagp == -1 || i < infos.flagp))
			write(1, &s[i], 1);
	}
	else
	{
		while (s[++i] && (infos.flagp == -1 || i < infos.flagp))
			write(1, &s[i], 1);
		while (l++ < infos.precision)
			ft_putchar(' ');
	}
	return (l - 1);
}

int	put_s_2(t_minishell infos, int l)
{
	char	*tmp;
	int		i;

	i = -1;
	tmp = ft_strdup("(null)\0");
	l = slen(tmp, infos);
	if (infos.flagm)
	{
		while (tmp[++i])
			if (infos.flagp == -1 || i < infos.flagp)
				ft_putchar(tmp[i]);
		while (l++ < infos.precision)
			ft_putchar(' ');
	}
	else
	{
		while (l++ < infos.precision)
			ft_putchar(' ');
		while (tmp[++i])
			if (infos.flagp == -1 || i < infos.flagp)
				ft_putchar(tmp[i]);
	}
	free(tmp);
	return (l - 1);
}

int	put_s3(char *s, t_minishell infos, int l)
{
	int	i;

	i = -1;
	while (l++ < infos.precision)
		ft_putchar('0');
	while (s[++i] && (infos.flagp == -1 || i < infos.flagp))
		write(1, &s[i], 1);
	return (l - 1);
}

int	ft_putstr_prec(char *s, t_minishell infos)
{
	int	i;
	int	l;

	i = -1;
	l = 0;
	if (infos.flagp == 0)
	{
		while (l++ < infos.precision)
			ft_putchar(' ');
		return (l - 1);
	}
	else if (s == NULL)
		return (put_s_2(infos, l));
	l = slen(s, infos);
	if (!infos.flagm && infos.precision > -1 && !infos.flagz)
		return (put_s(s, infos, l, 1));
	else if (!infos.flagm && infos.flagz && infos.precision > -1)
		return (put_s3(s, infos, l));
	else if (infos.flagm)
		return (put_s(s, infos, l, 0));
	else
		while (s[++i] && (infos.flagp == -1 || i < infos.flagp))
			write(1, &s[i], 1);
	return (i);
}
