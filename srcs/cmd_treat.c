/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_treat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bycop <bycop@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 13:06:04 by bycop          #+#    #+#             */
/*   Updated: 2021/09/22 13:01:50 by bycop         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*quote_treatment(char *s, int *i)
{
	int		start;
	char	*res;

	start = *i;
	res = ft_strdup("");
	while (s[++(*i)] && quote_type(s[*i]) != quote_type(s[start]))
	{
		if (s[*i] == '$' && (s[*i - 1] && s[*i - 1] != '\\')
			&& quote_type(s[start]) != 2 && s[*i + 1] && s[*i + 1] != ' ')
		{
			res = ft_strjoinfree(res, env_get(ft_substr(s, *i + 1,
							next_space(s + *i + 1, 2)), 0, NULL, NULL), 3);
			*i += next_space(s + *i + 1, 2);
		}
		else if (s[*i] != '\\' || (s[*i - 1] && s[*i - 1] == '\\'))
			res = ft_strljoinfree(res, s + *i, 1);
	}
	return (res);
}

char	*args_treatment_while(int i, char *s)
{
	char	*res;

	res = ft_strdup("");
	while (++i <= (int)ft_strlen(s) && s[i])
	{
		if (quote_type(s[i]) && (i == 0 || s[i - 1] != '\\'))
			res = ft_strjoinfree(res, quote_treatment(s, &i), 3);
		else if (s[i] == '$' && (i == 0 || s[i - 1] != '\\')
			&& s[i + 1] && s[i + 1] != ' ')
		{
			res = ft_strjoinfree(res, env_get(ft_substr(s, i + 1,
							next_space(s + i + 1, 2)), 0, NULL, NULL), 3);
			i += next_space(s + i + 1, 2);
		}
		else if (s[i] == '~' && (i == 0 || (s[i - 1] != '\\'
					&& !ft_isalnum(s[i - 1]))) && (!s[i + 1]
				|| s[i + 1] == '/' || s[i + 1] == ' '))
			res = ft_strjoinfree(res, env_get("HOME", 0, NULL, NULL), 3);
		else if ((s[i] != ' ' && (s[i] != '\\'
					|| ((i == 0 && s[i] != '\\')
						|| (i != 0 && s[i - 1] == '\\'))))
			|| (i != 0 && s[i - 1] != ' ' && s[i + 1] && s[i] != '\\'))
			res = ft_strljoinfree(res, s + i, 1);
	}
	return (res);
}

void	args_treatment(t_cmd *cmd)
{
	int		i;
	int		j;
	char	*res;
	char	*s;

	j = -1;
	while (++j < cmd->nb_args)
	{
		res = ft_strdup("");
		s = cmd->args[j];
		i = -1;
		res = args_treatment_while(i, s);
		free(cmd->args[j]);
		cmd->args[j] = ft_strdup(res);
		free(res);
	}
}
