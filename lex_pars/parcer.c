/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:33:46 by kdvarako          #+#    #+#             */
/*   Updated: 2024/10/01 18:13:43 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	if_any_word(enum e_tokentype type)
{
	if (type == WORD || type == EXPAND_VAR || type == EXPAND_VAR_Q)
		return (1);
	return (0);
}

char	*save_cmd(char *cmd)
{
	int		i;

	i = 0;
	while (cmd[i] != '\0')
	{
		cmd[i] = ft_tolower(cmd[i]);
		i++;
	}
	return (cmd);
}

t_token	*save_redir(t_token *node, t_env **env, t_redirect **redirs)
{
	char	*rtype;
	char	*rfile;

	rtype = NULL;
	rfile = NULL;
	rtype = ft_strndup(node->ptr, node->len);
	node = node->next;
	while (node->type == SEPARATOR)
		node = node->next;
	if (node->type == WORD || node->type == EXPAND_VAR \
		|| node->type == EXPAND_VAR_Q)
		rfile = save_word(&node, env);
	add_redir(rtype, rfile, redirs);
	return (node);
}

t_token	*save_pipe(t_token *node, char *cmd, t_env **env, t_parc **parc)
{
	t_arg		*args;
	t_redirect	*redirs_in;
	t_redirect	*redirs_out;

	redirs_in = NULL;
	redirs_out = NULL;
	args = NULL;
	while (node != NULL && node->type != PIPE)
	{
		if (node != NULL && (if_any_word(node->type) == 1) && cmd == NULL)
			cmd = save_cmd(save_word(&node, env));
		else if (node != NULL && (node->type == REDIR_IN \
			|| node->type == REDIR_IN2))
			node = save_redir(node, env, &redirs_in);
		else if (node != NULL && (node->type == REDIR_OUT \
			|| node->type == REDIR_OUT2))
			node = save_redir(node, env, &redirs_out);
		else if (node != NULL && (if_any_word(node->type) == 1))
			add_args(save_word(&node, env), &args);
		//else if (node != NULL && node->type == SEPARATOR && args != NULL)
			//add_args(ft_strndup(" ", 1), &args);
		node = node->next;
	}
	ft_plst_add_back(parc, ft_plst_new(cmd, args, redirs_in, redirs_out));
	return (node); /*free redirs, args ?*/
}

void	parcer(t_token **token, t_parc **parc, t_env **env)
{
	t_token		*node;
	char		*cmd;

	if (!token)
		return ;
	node = *token;
	while (node != NULL)
	{
		cmd = NULL;
		node = save_pipe(node, cmd, env, parc);
		if (node != NULL)
			node = node->next;
		//free cmd ?
	}
	//save_exit_status_parc(parc, exit_status);
}
