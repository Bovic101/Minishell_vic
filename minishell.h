/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:18:18 by kdvarako          #+#    #+#             */
/*   Updated: 2024/09/09 07:16:40 by vodebunm         ###   ########.fr       */
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
# include <sys/types.h>//PID
# include <sys/wait.h>// waitpid
# include <fcntl.h>
# include <stddef.h>
# include <stdbool.h>
# include <string.h>
# include <signal.h>

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
*/

typedef struct s_parc
{
	char				*cmd;
	struct s_arg		*args;
	struct s_redirect	*redirs_in;
	struct s_redirect	*redirs_out;
	struct s_parc		*next;
}	t_parc;

/*
structure to save env: key=value
$? - status of the most recently executed pipeline
-> value of the variable "exit_code" in env
"exit_code" is a nonprintable variable
*/

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

/*
structure to save a history of commands:
rline - a current readline
next - next cmd
prev - privios cmd
*/

typedef struct s_history
{
	char				*rvalue;
	struct s_history	*next;
	struct s_history	*prev;
}	t_history;

//lexer - tokenizer in lex_parc
void		lexer(t_token **token, char *s);
t_token		*ft_lst_new(int len, char *ptr, enum e_tokentype type);
void		ft_lst_add_back(t_token **token, t_token *new);
void		ft_lst_print(t_token **token);
//free memory: token, parc
void		freeall(t_token **token, t_parc **parc);
//parcer in lex_parc
void		parcer(t_token **token, t_parc **parc, t_env **env);
t_parc		*ft_plst_new(char *cmd, t_arg *args, \
				t_redirect *redirs_in, t_redirect *redirs_out);
void		ft_plst_add_back(t_parc **parc, t_parc *new);
void		ft_plst_print(t_parc **parc);
char		*save_word(t_token **pnode, t_env **env);
char		*expand(char *ptr, int len, t_env **env, int type);
void		add_redir(char *rtype, char	*rfile, t_redirect **redirs);
void		ft_redir_print(t_redirect **redirs);
void		add_args(char *value, t_arg **args);
void		ft_arg_print(t_arg **args);
char		*ft_strndup(const char *str, size_t n);
//environment
void		save_environment(char **envp, t_env **env);
t_env		*ft_env_new(char *key, char *value);
void		ft_env_add_back(t_env **lst, t_env *new);
//to print env
void		ft_env_print(t_env **env);
void		prompt(void);
//to sort and print env with declare
void		ft_env_sort_declare(t_env *env);
void		add_env(char *key, char *value, t_env **env);
int			ft_strcmp(char *s1, char *s2);
void		ft_free_env(t_env	**env);
//return value of the key-variable from env
char		*get_value(char *key, t_env **env);
//set a new value to env (new_value must be allocated)
void		set_value(char *key, char *new_value, t_env **env);
//remove info from env
void		remove_node(char *key, t_env **env);
//funtions for the history of commands:
void		save_history(char *s, t_history **history);
t_history	*ft_history_new(char *rvalue);
void		ft_history_add_back(t_history **lst, t_history *new);
void		ft_free_history(t_history	**history);
void		ft_history_print(t_history **history);
//execution part:
//void		execute(t_parc **parc, t_env **env);
char		**arg_to_array_converter(t_arg *arg , char *command);
char		**env_to_array_converter(t_env *env);
char		*ft_strcpy(char *dest, const char *src);
char		*ft_strcat(char *dest, const char *src);
char		*str_tokenizer(char *str, const char *delim);
char		*command_fullpath_finder(char *command, t_env **env);
void		redirection_func(t_redirect *in_redir, t_redirect *out_redir);
void		pipe_func(t_parc *command, t_env **env);
void		executor_func(t_parc *command, t_env **env);
void		redir_execute_command(t_parc *command, t_env **env);
void		handle_error_msg(const char *cmd);
//find size of structures (how many nodes) - in the file ft_list_size.c:
int			ft_size_parc(t_parc *lst);
int			ft_size_arg(t_arg *lst);
int			ft_size_redirect(t_redirect *lst);
int			ft_size_env(t_env *lst);
//signals
void		sigint_handler(int signal);
void		sigquit_handler(int signal);
#endif