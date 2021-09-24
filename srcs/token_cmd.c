/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperrier <jperrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 10:47:01 by jperrier          #+#    #+#             */
/*   Updated: 2021/09/22 10:39:39 by jperrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_cmd(t_token *tok)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (1);
	g_minishell.cmd = cmd;
	split_args(cmd, tok->str);
	args_treatment(cmd);
	find_cmd(cmd, -1, 0, NULL);
	free_cmd(cmd);
	g_minishell.cmd = NULL;
	return (0);
}
