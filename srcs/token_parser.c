/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperrier <jperrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 14:53:43 by jperrier          #+#    #+#             */
/*   Updated: 2021/09/23 16:15:57 by jperrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int	is_separator(char *str, int *sep_size)
{
	static char	*separators[] = {"|", "<<", ">>", "<", ">", ";"};
	int			size;
	int			i;

	size = 6;
	i = 0;
	while (i < size)
	{
		if (ft_strncmp(separators[i], str, ft_strlen(separators[i])) == 0)
		{
			*sep_size = ft_strlen(separators[i]);
			return (i + 1);
		}
		i++;
	}
	*sep_size = -1;
	if (*str == 0)
		return (-1);
	return (-1);
}

static int	add_token(int type, char *str)
{	
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (1);
	tok->str = str;
	tok->type = type;
	tok->next = NULL;
	tok->prev = NULL;
	token_add_last(&g_minishell.tokens, tok);
	return (0);
}

typedef struct s_parser
{
	int				i;
	int				start;
	int				dquote;
	int				squote;
	int				sep_type;
	int				last_sep;
	int				sep_size;
}				t_parser;

static void	in_loop(t_parser *p)
{
	p->sep_type = is_separator(&g_minishell.original[p->i], &p->sep_size);
	if (p->sep_type > -1 && p->dquote % 2 == 0 && p->squote % 2 == 0)
	{
		if (p->last_sep > -1 && p->last_sep != PIPE && p->last_sep != SEP)
			add_token(p->last_sep,
				ft_substr(g_minishell.original, p->start, p->i - p->start));
		else
			add_token(CMD, ft_substr(g_minishell.original,
					p->start, p->i - p->start));
		if (p->sep_type == PIPE || p->sep_type == SEP)
			add_token(p->sep_type, NULL);
		p->last_sep = p->sep_type;
		p->start = p->i + p->sep_size;
		p->i = p->start;
	}
}

static void	loop(t_parser *p)
{
	while (g_minishell.original[p->i])
	{
		if (g_minishell.original[p->i] == '"' && p->squote % 2 == 0
			&& (!g_minishell.original[p->i - 1]
				|| g_minishell.original[p->i - 1] != '\\'))
			p->dquote++;
		else if (g_minishell.original[p->i] == '\'' && p->dquote % 2 == 0
			&& (!g_minishell.original[p->i - 1]
				|| g_minishell.original[p->i - 1] != '\\'))
			p->squote++;
		else
		{
			in_loop(p);
		}
		if (g_minishell.original[p->i])
			p->i++;
	}
}

int	parse_line(void)
{
	t_parser	p;
	int			type;
	char		*str;

	p.last_sep = -1;
	p.dquote = 2;
	p.squote = 2;
	p.start = 0;
	p.i = 0;
	loop(&p);
	if (p.dquote % 2 == 0 && p.squote % 2 == 0)
	{
		str = ft_substr(g_minishell.original, p.start, p.i - p.start);
		type = CMD;
		if (p.last_sep > -1 && p.last_sep != PIPE && p.last_sep != SEP)
			type = p.last_sep;
		if (add_token(type, str) == -1)
			free(str);
	}
	else
	{
		ft_printf(1, "Error: Missing quote\n");
		return (1);
	}
	return (0);
}
