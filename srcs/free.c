/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperrier <jperrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 11:33:21 by sfournio          #+#    #+#             */
/*   Updated: 2021/09/22 11:25:30 by jperrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_tokens(void)
{
	t_token	*tmp;
	t_token	*tok;

	tok = g_minishell.tokens;
	if (!tok)
		return ;
	while (tok)
	{
		tmp = tok;
		tok = tmp->next;
		if (tmp->str)
			free(tmp->str);
		free(tmp);
	}
}

void	free_env(void)
{
	int	i;

	i = 0;
	while (g_minishell.env[i] != NULL)
		free(g_minishell.env[i++]);
	if (g_minishell.env)
		free(g_minishell.env);
}

void	free_loop(void)
{
	int	i;

	i = -1;
	free(g_minishell.original);
	free_tokens();
}

void	free_all(void)
{
	if (g_minishell.cmd != NULL)
		free_cmd(g_minishell.cmd);
	free_loop();
	free_env();
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd == NULL)
		return ;
	while (i < cmd->nb_args)
		free(cmd->args[i++]);
	if (cmd->args)
		free(cmd->args);
	if (cmd)
		free(cmd);
}
