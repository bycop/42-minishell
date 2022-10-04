/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd_fictif.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperrier <jperrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 10:29:18 by bycop          #+#    #+#             */
/*   Updated: 2021/09/22 11:29:08 by jperrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fictif_multi(int *i, int *j, char *buf, t_cmd *cmd)
{
	char	*buf3;
	char	*buf2;
	int		save;

	save = *i;
	*i = ft_strlen(buf);
	buf2 = NULL;
	while (*j > 0)
	{
		free(buf2);
		buf2 = found_slash(buf2, buf, i);
		*j -= 1;
	}
	if (cmd->args[1][save])
	{
		buf3 = ft_strjoin("/", cmd->args[1] + save);
		ft_strlcpy(buf2 + ft_strlen(buf2), buf3, ft_strlen(buf3) + 1);
		free(buf3);
	}
	return (buf2);
}

int	fictif_simple(char *buf, char *buf2, int i, t_cmd *cmd)
{
	getcwd(buf, 1000);
	i = ft_strlen(buf);
	if (cmd->args[1][1] == '.' && (cmd->args[1][2]
			&& cmd->args[1][2] != '/'))
		return (cd_errors(ENOENT, cmd));
	if (cmd->args[1][1] == '.' && !cmd->args[1][2])
	{
		buf2 = found_slash(buf2, buf, &i);
		if (chdir(buf2) == -1)
		{
			free(buf2);
			return (cd_errors(errno, cmd));
		}
		free(buf2);
		return (0);
	}
	return (1);
}

int	fictif_main(char *buf, char *buf2, t_cmd *cmd)
{		
	int	i;
	int	j;
	int	ret;

	i = 0;
	ret = fictif_simple(buf, buf2, i, cmd);
	if (ret != 1)
		return (ret);
	i = 0;
	j = 0;
	while (ft_strncmp(cmd->args[1] + i, "../", 3) == 0)
	{
		i += 3;
		j++;
	}
	buf2 = fictif_multi(&i, &j, buf, cmd);
	if (chdir(buf2) == -1)
	{
		free(buf2);
		return (cd_errors(errno, cmd));
	}
	free(buf2);
	return (0);
}
