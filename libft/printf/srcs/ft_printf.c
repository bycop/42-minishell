/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperrier <jperrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 03:06:28 by sfournio          #+#    #+#             */
/*   Updated: 2021/09/16 09:07:08 by jperrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_minishell	main_while(const char *str, t_minishell infos, va_list va)
{
	int	index;

	index = 0;
	while (str[index])
	{
		infos = init_global_printf(infos, 0);
		if (str[index] == '%')
		{
			infos = check_flags(&str[index + 1], infos, &index, va);
			infos.length += check_type(&str[index + 1], infos, va, &index);
		}
		else
			infos.length += ft_putchar(str[index]);
		if (str[index])
			index++;
	}
	return (infos);
}

t_minishell	init_global_printf(t_minishell infos, int reset)
{
	if (reset == 1)
		infos.length = 0;
	infos.precision = -1;
	infos.flagp = -1;
	infos.flagm = 0;
	infos.flagz = 0;
	return (infos);
}

int	ft_printf(int fd, const char *str, ...)
{
	va_list		va;
	t_minishell	infos;
	int			back;

	back = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	infos.length = 0;
	infos = init_global_printf(infos, 1);
	va_start(va, str);
	infos = main_while(str, infos, va);
	va_end(va);
	dup2(back, STDOUT_FILENO);
	close(back);
	return (infos.length);
}
