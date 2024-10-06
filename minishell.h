/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:18:18 by kdvarako          #+#    #+#             */
/*   Updated: 2024/10/06 11:00:28 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stddef.h>
# include <stdbool.h>
# include <string.h>
# include <signal.h>
# include <limits.h>

enum e_tokentype
{
	WORD,
	SEPARATOR,
	REDIR_IN,
	REDIR_OUT,
	REDIR_IN2,
	REDIR_OUT2,
	EXPAND_VAR,
	EXPAND_VAR_Q,
	PIPE
};
typedef struct s_token
{
	int					len;
	char				*ptr;
	enum e_tokentype	type;
	struct s_token		*next;
}		t_token;

//structure for arguments: array of char

typedef struct s_arg
{
	char			*value;
	struct s_arg	*next;
}	t_arg;

//structure for redirection: type(<,<<,>,>>) - name_of_file

typedef struct s_redirect
{
	char				*rtype;
	char				*rfile;
	struct s_redirect	*next;
}	t_redirect;

/*
structure to execute: 
command - array_struct_of_arguments - array_struct_of_redirection
fd_0 - read, fd_1 - write
*/

typedef struct s_parc
{
	char				*cmd;
	struct s_arg		*args;
	struct s_redirect	*redirs_in;
	struct s_redirect	*redirs_out;
	int					fd_0;
	int					fd_1;
	char				*hdoc;
	struct s_parc		*next;
}	t_parc;

/*
structure to save env: key = value
($? - exit status of the most recently executed pipeline
-> variable "exit_status" in env)
*/

typedef struct s_env
{
	int				*exit_status;
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

//lexer - tokenizer in lex_parc
void		lexer(t_token **token, char *s);
t_token		*ft_lst_new(int len, char *ptr, enum e_tokentype type);
void		ft_lst_add_back(t_token **token, t_token *new);
void		ft_lst_print(t_token **token);
void		lexer_redir_in(char *s, int *i, int *len, enum e_tokentype *type);
void		lexer_redir_out(char *s, int *i, int *len, enum e_tokentype *type);
char		*lexer_double_quotes(char *s, int *i, \
				int *len, enum e_tokentype *type);
char		*lexer_single_quotes(char *s, int *i, \
				int *len, enum e_tokentype *type);
void		lexer_word(char *s, int *i, int *len, enum e_tokentype *type);
//free memory: token, parc, env
void		freeall(t_env **env, t_parc **parc);
void		ft_free_token(t_token **token);
void		ft_free_parc(t_parc **parc);
void		ft_free_env(t_env	**env);
//parcer in lex_parc
void		parcer(t_token **token, t_parc **parc, t_env **env);
t_parc		*ft_plst_new(char *cmd, t_arg *args, \
				t_redirect *redirs_in, t_redirect *redirs_out);
void		ft_plst_add_back(t_parc **parc, t_parc *new);
void		ft_plst_print(t_parc **parc);
char		*save_word(t_token **pnode, t_env **env);
char		*ft_wordjoin(char *value, char *str);
char		*expand(char *ptr, int len, t_env **env, int type);
char		*ft_remove_spaces(char *value);
void		add_redir(char *rtype, char	*rfile, t_redirect **redirs);
void		ft_redir_print(t_redirect **redirs);
void		add_args(char *value, t_arg **args);
void		ft_arg_print(t_arg **args);
char		*ft_strndup(const char *str, size_t n);
//environment
void		save_environment(char **envp, t_env **env, int *exit_status);
t_env		*ft_env_new(char *key, char *value);
void		ft_env_add_back(t_env **lst, t_env *new);
void		shell_loop(t_env **env);
//to print env
void		ft_env_print(t_env **env);
void		prompt(void);
//to sort and print env with declare
void		ft_env_sort_declare(t_env *env);
void		add_env(char *key, char *value, t_env **env);
void		add_set_env(char *key, char *value, t_env **env);
int			ft_strcmp(char *s1, char *s2);
//return value of the key-variable from env
char		*get_value(char *key, t_env **env);
//set a new value to env (new_value must be allocated)
void		set_value(char *key, char *new_value, t_env **env);
//remove info from env
void		remove_node(char *key, t_env **env);
//find key in env: 1-found, 0-not found
int			find_key_env(char *key, t_env **env);
//pipes
void		create_pipes(t_parc **parc, t_env **env);
void		close_fds(t_parc **parc);
//execution part:
char		**arg_to_array_converter(t_arg *arg, char *command);
char		**env_to_array_converter(t_env *env);
char		*ft_strcpy(char *dest, const char *src);
char		*ft_strcat(char *dest, const char *src);
char		*str_tokenizer(char *str, const char *delim);
char		*command_fullpath_finder(char *command, t_env **env);
void		executor_func(t_parc *command, t_env **env);
void		handle_error_msg(const char *cmd);
void		run_2nd_minishell(t_parc *parc, t_env **env);
int			unclosed_quote_checker(const char *str);
int			count_env_vars(t_env *env);
char		*prepare_command(t_parc *command, t_env **env, char ***argv, char ***env_list);
char		*find_in_path_env(char *command, char *path_env_copy);
//find size of structures (how many nodes) - in the file ft_list_size.c:
int			ft_size_parc(t_parc *lst);
int			ft_size_arg(t_arg *lst);
int			ft_size_redirect(t_redirect *lst);
int			ft_size_env(t_env *lst);
//signals
void		sigint_handler(int signal);
void		sigquit_handler(int signal);
int			eof_handler(int count, int key);
void		signal_handlers_caller(void);
//builtin
int			execute_builtin(t_parc *parc, t_env **env);
int			if_builtin(char *cmd); // func returns 0 if cmd is builtin
int			exe_echo(t_parc *node);
int			exe_cd(t_parc *node, t_env **env);
int			exe_env(t_env **env);
int			exe_export(t_parc *node, t_env **env);
int			exe_pwd(t_env **env);
int			exe_unset(t_parc *node, t_env **env);
int			exe_exit(t_parc *node, t_env **env);
//redirections
int			save_all_hdoc(t_parc **parc);
int			ft_redirections(t_parc *node);
int			redir_out(t_parc *node);
int			redir_in(t_parc *node);
int			start_execute(t_parc **parc, t_env **env);
int			ft_execute(t_parc *node, t_env **env);
//errors
void		print_error_msg(char *cmd, char *arg, char *msg);
#endif
