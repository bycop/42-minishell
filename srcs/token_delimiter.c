/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_delimiter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperrier <jperrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 16:52:29 by jperrier          #+#    #+#             */
/*   Updated: 2021/09/23 15:28:37 by jperrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_delimiter(t_token *tok)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (1);
	split_args(cmd, tok->str);
	addparams(cmd);
	args_treatment(cmd);
	if (str_is_empty(tok->prev->str))
		return (tok_err(tok));
	g_minishell.input_mode = 1;
	g_minishell.delimiter = ft_strdup(cmd->args[0]);
	if (pipe(g_minishell.delimiter_pipes) == -1)
		return (1);
	free(cmd);
	return (0);
}
