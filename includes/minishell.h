/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperrier <jperrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 12:11:23 by bycop          #+#    #+#             */
/*   Updated: 2021/09/23 15:45:25 by jperrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define CMD_NOTFOUND "command not found"
# define EXEC_NAME "Minishell"

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>

// Compil linux
# include <sys/types.h>
# include <sys/wait.h>

# include <errno.h>
# include "libft.h"
# include <termios.h>
# include <signal.h>
# include <curses.h>
# include <term.h>

# define OLDPWD_CODE 667
# define OLDPWD_ERR "OLDPWD not set"
# define ENOENT_ERR "No such file or directory"
# define ENOTDIR_ERR "Not a directory"
# define EACCES_ERR "Permission denied"
# define KERNEL_REGISTER "failed to register interrupts with kernel"
# define INV_ID "not a valid identifier"
# define UNEX_TOKEN "syntax error near unexpected token"
# define IS_DIR "is a directory"

# define UNKNOWN -1
# define CMD 0
# define PIPE 1
# define DELIMITER 2
# define APPEND 3
# define INPUT 4
# define TRUNC 5
# define SEP 6

typedef struct s_cmd
{
	char		**args;
	int			nb_args;
}				t_cmd;

typedef struct s_token	t_token;

typedef struct s_token
{
	char			*str;
	int				type;
	t_token			*next;
	t_token			*prev;
}					t_token;

typedef struct s_minishell
{
	int				return_value;
	char			**env;
	char			**paths;
	char			*original;
	t_token			*tokens;
	char			*prompt;
	int				fd_input_o;
	int				fd_output_o;
	int				fd_input;
	int				fd_output;
	int				double_slash;
	t_token			*cmd_token;
	int				pipe_in;
	int				pipe_out;
	int				left_pipe[2];
	int				right_pipe[2];
	t_cmd			*cmd;
	int				input_mode;
	char			*delimiter;
	char			*delimiter_str;
	int				delimiter_pipes[2];
}					t_minishell;

t_minishell				g_minishell;

/*
**					Init & free
*/

int					init_cmd(void);
int					init_minishell(char **envp);
void				free_loop(void);
void				free_all(void);
int					reset_minishell(void);
void				free_cmd(t_cmd *cmd);

/*
**					READLINE
*/

void				handle_signals(int signo);
void				wait_input(void);
void				set_prompt(void);

/*
**					PARSERS
*/
int					parse_line(void);
char				**split_args(t_cmd *cmd, char *str);
void				args_treatment(t_cmd *cmd);

/*
**					EXECUTION
*/

void				find_cmd(t_cmd *cmd, int i, int found, char *lower);
void				ft_echo(t_cmd *cmd);
void				ft_cd(t_cmd *cmd);
void				ft_pwd(t_cmd *cmd);
void				ft_exit(t_cmd *cmd);
void				ft_unset(t_cmd *cmd);
void				ft_export(t_cmd *cmd);
void				ft_env(t_cmd *cmd);

int					ft_cd_main(t_cmd *cmd);
int					cd_errors(int err, t_cmd *cmd);
char				*fictif_multi(int *i, int *j, char *buf, t_cmd *cmd);
int					fictif_simple(char *buf, char *buf2, int i, t_cmd *cmd);
int					fictif_main(char *buf, char *buf2, t_cmd *cmd);

/*
**					UTILS
*/

int					quote_type(char c);
int					sep_type(char c, char next);
char				**ft_strsjoin(char **s1, char *s2);
char				**ft_strsjoin_nofree(char **s1, char *s2);
int					next_space(char *s, int type);
int					check_space(char *input);
int					skip_space(char *s);
char				*found_slash(char *buf2, char *buf, int *i);
char				*str_tolower(char *str);
int					str_is_empty(char *str);
int					ret_error(int error);
void				set_error(int error);

/*
**					ENV
*/

int					env_free(void);
char				*env_get(char *name, int i, char *key, char *pwd);
int					env_contains(char *name);
void				env_print_alphaorder(int i, int j, char *last, char *low);
int					env_name_valid(char *line);
int					env_set(char *name, char *value, int i, char *v);
char				*env_value(char *line);
char				*env_key(char *line);
int					env_init(char **envp);
void				extract_paths(void);
int					found_cmd(t_cmd *cmd, int found, int j);
void				strs_free(char **strs);
int					env_len(void);
void				env_print(int fd);
int					env_unset(char *name, int i, int j, char *tname);
char				*remove_dquote(char *value);

/*
**					TOKENS
*/

t_token				*token_last(t_token *lst);
void				token_add_last(t_token **lst, t_token *cmd);
int					process_tokens(void);
int					token_cmd(t_token *tok);
int					token_trunc(t_token *tok);
int					token_append(t_token *tok);
int					token_input(t_token *tok);
int					token_pipe(void);
int					token_delimiter(t_token *tok);

void				path_child(char *command, char **cmd);
void				path_parent(pid_t pid, int status);
void				token_print(int token);
void				addparams(t_cmd *cmd);
int					tok_err(t_token *tok);
#endif
