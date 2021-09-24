/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperrier <jperrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 14:52:24 by jperrier          #+#    #+#             */
/*   Updated: 2021/09/22 11:26:17 by jperrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_pipe(void)
{
	int	fd1;
	int	fd2;

	fd1 = g_minishell.right_pipe[0];
	fd2 = g_minishell.right_pipe[1];
	g_minishell.right_pipe[0] = g_minishell.left_pipe[0];
	g_minishell.right_pipe[1] = g_minishell.left_pipe[1];
	g_minishell.left_pipe[0] = fd1;
	g_minishell.left_pipe[1] = fd2;
	return (0);
}
