/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperrier <jperrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 03:18:24 by sfournio          #+#    #+#             */
/*   Updated: 2021/09/16 09:07:08 by jperrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_global
{
	int		length;
	int		flagp;
	int		flagz;
	int		flagm;
	int		precision;
}	t_minishell;

int					ft_printf(int fd, const char *str, ...);

/*
**			Basic printers
*/
int					ft_putchar(char c);
int					ft_putnbr(int n);
int					ft_putstr(char *s);
int					ft_putchar_pourcent(char c, t_minishell infos);

/*
**			Main functions
*/
t_minishell			check_flags(const char *str, t_minishell infos, int *ind,
						va_list va);
t_minishell			init_global_printf(t_minishell infos, int reset);
t_minishell			check_prec(const char *str, t_minishell infos, int *ind,
						va_list va);
int					check_type(const char *str, t_minishell infos, va_list va,
						int *ind);

/*
**			%d %i and %u
*/
int					ft_put_d_i(t_minishell infos, va_list va);
int					ft_put_u(t_minishell infos, va_list va);
int					ft_putnbr_u(int n);
int					intlen(int nb);

/*
**			%s and %c
*/
int					ft_putchar_c(char c, t_minishell infos);
int					ft_putstr_prec(char *s, t_minishell infos);

/*
**			%x and %X
*/
int					ft_putstr_hex(char *s, t_minishell infos);
char				*ft_itoa_base(int value);

/*
**			%p flag
*/
int					f_p(char *s, t_minishell infos);
char				*ft_itoa_b_a(unsigned long long value, t_minishell infos);

/*
**			Mini lib
*/
int					ft_atoi(const char *str);
char				*ft_strdup(const char *src);
int					ft_strlen(const char *str);

/*
**			Others
*/
char				*ft_tolow(char *s);
char				*ft_strrev(char *src);
int					pointlen(int j, t_minishell infos);
char				*little(char *nbr, int i, int *ind);
t_minishell			little2(t_minishell infos);

#endif
