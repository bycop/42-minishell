/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperrier <jperrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 11:10:19 by jperrier          #+#    #+#             */
/*   Updated: 2021/09/23 15:30:04 by jperrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*token_last(t_token *lst)
{
	t_token	*next;

	if (lst != NULL)
	{
		next = lst;
		while (1)
		{
			if (next->next == NULL)
				return (next);
			next = next->next;
		}
	}
	return (NULL);
}

void	token_add_last(t_token **lst, t_token *tok)
{
	t_token	*last;

	if (!lst)
		return ;
	if (*lst == NULL)
	{
		*lst = tok;
		tok->prev = NULL;
	}
	else
	{
		last = token_last(*lst);
		last->next = tok;
		tok->prev = last;
	}
}

void	addparams(t_cmd *cmd)
{
	int	i;

	i = 1;
	while (i < cmd->nb_args)
	{
		if (g_minishell.cmd_token->str[0] != '\0')
			g_minishell.cmd_token->str
				= ft_strjoinfree(g_minishell.cmd_token->str, " ", 1);
		g_minishell.cmd_token->str
			= ft_strjoinfree(g_minishell.cmd_token->str, cmd->args[i], 1);
		i++;
	}
}
