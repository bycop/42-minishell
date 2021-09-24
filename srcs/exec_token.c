/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperrier <jperrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 10:48:16 by jperrier          #+#    #+#             */
/*   Updated: 2021/09/23 16:14:02 by jperrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_cmd(t_token *tok)
{
	g_minishell.pipe_in = 0;
	g_minishell.pipe_out = 0;
	if (tok->next != NULL && tok->next->type == PIPE)
		g_minishell.pipe_out = 1;
	if (tok->prev != NULL && tok->prev->type == PIPE)
		g_minishell.pipe_in = 1;
	if (tok->str[0] == '\0')
		return (0);
	return (token_cmd(tok));
}

int	tok_err(t_token *tok)
{
	static char	*separators[] = {"|", "<<", ">>", "<", ">", ";"};

	g_minishell.return_value = 258;
	ft_printf(2, "\e[91m%s: \e[0m%s `%s`\n",
		EXEC_NAME, UNEX_TOKEN, separators[tok->type - 1]);
	return (1);
}

static int	process2(t_token *tok, int return_value)
{
	if (tok->type == INPUT)
	{
		return_value = token_input(tok);
		if (str_is_empty(tok->prev->str))
			return (tok_err(tok));
	}
	else if (tok->type == TRUNC)
	{
		return_value = token_trunc(tok);
		if (str_is_empty(tok->prev->str))
			return (tok_err(tok));
	}
	else if (tok->type == SEP)
	{
		if (tok->next == NULL || tok->next->type != CMD
			|| tok->prev == NULL || str_is_empty(tok->prev->str))
			return (tok_err(tok));
		return_value = 0;
	}
	else
		return_value = 1;
	return (return_value);
}

static int	process_token(t_token *tok, int return_value)
{
	if (tok->type == CMD)
		g_minishell.cmd_token = tok;
	else if (tok->type == PIPE)
	{
		if (tok->next == NULL || tok->next->type != CMD
			|| tok->prev == NULL || str_is_empty(tok->prev->str))
			return (tok_err(tok));
		if (g_minishell.cmd_token != NULL)
			return_value = exec_cmd(g_minishell.cmd_token);
		token_pipe();
	}
	else if (tok->type == DELIMITER)
		return_value = token_delimiter(tok);
	else if (tok->type == APPEND)
	{
		return_value = token_append(tok);
		if (str_is_empty(tok->prev->str))
			return (tok_err(tok));
	}
	else
		return_value = process2(tok, return_value);
	if (g_minishell.cmd_token && (tok->next == NULL || tok->next->type == SEP))
		return (exec_cmd(g_minishell.cmd_token));
	return (return_value);
}

int	process_tokens(void)
{
	t_token	*tok;

	tok = g_minishell.tokens;
	if (!tok)
		return (1);
	while (tok)
	{
		if (process_token(tok, 0))
			return (1);
		tok = tok->next;
	}
	return (0);
}
