/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperrier <jperrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 13:56:17 by jperrier          #+#    #+#             */
/*   Updated: 2021/09/22 15:41:46 by jperrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_input(t_token *tok)
{
	t_cmd	*cmd;
	int		fd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (1);
	split_args(cmd, tok->str);
	args_treatment(cmd);
	fd = open(cmd->args[0], O_RDONLY, S_IRWXU);
	if (fd == -1)
		return (1);
	dup2(fd, STDIN_FILENO);
	free(cmd);
	return (0);
}
