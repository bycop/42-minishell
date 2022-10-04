/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperrier <jperrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 10:45:11 by bycop          #+#    #+#             */
/*   Updated: 2021/09/23 13:00:42 by jperrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	only_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if ((str[i] == '-' || str[i] == '+') && !ft_isdigit(str[++i]))
		return (0);
	while (str[i] && ft_isdigit(str[i]))
		i++;
	while (str[i] == ' ')
		i++;
	if (!str[i])
		return (1);
	return (0);
}

int	int_max(char	*str)
{
	long long	res;
	int			i;
	int			neg;

	i = 0;
	res = 0;
	neg = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		if (res > INT_MAX || res * neg < INT_MIN)
			return (1);
		i++;
	}
	return (0);
}

void	ft_exit(t_cmd *cmd)
{
	int		value;

	value = 0;
	ft_printf(1, "exit\n");
	if (cmd->nb_args > 2)
	{
		ft_printf(2, "\e[91m%s: \e[0mexit: too many arguments\n",
			EXEC_NAME, cmd->args[1]);
		g_minishell.return_value = 1;
		return ;
	}
	else if (cmd->args[1] && (!only_digit(cmd->args[1])
			|| int_max(cmd->args[1])))
	{
		ft_printf(2, "\e[91m%s: \e[0mexit: numeric argument required\n",
			EXEC_NAME, cmd->args[1]);
		value = 255;
	}
	else if (cmd->args[1])
		value = ft_atoi(cmd->args[1]) % 256;
	if (value == -1)
		value = 255;
	free_all();
	exit(value);
}
