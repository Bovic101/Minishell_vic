/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:41:54 by kdvarako          #+#    #+#             */
/*   Updated: 2024/10/08 03:23:08 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_token(t_token **token)
{
	t_token	*node;
	t_token	*tmp;

	if (!token)
		return ;
	tmp = *token;
	while (tmp)
	{
		node = tmp->next;
		free(tmp);
		tmp = node;
	}
	*token = NULL;
}

void	ft_free_args(t_arg **args)
{
	t_arg	*node;
	t_arg	*tmp;

	if (!args)
		return ;
	tmp = *args;
	while (tmp)
	{
		free(tmp->value);
		node = tmp->next;
		free(tmp);
		tmp = node;
	}
	*args = NULL;
}

void	ft_free_redirs(t_redirect **redirs)
{
	t_redirect	*node;
	t_redirect	*tmp;

	if (!redirs)
		return ;
	tmp = *redirs;
	while (tmp)
	{
		free(tmp->rtype);
		free(tmp->rfile);
		node = tmp->next;
		free(tmp);
		tmp = node;
	}
	*redirs = NULL;
}

void	ft_free_parc(t_parc **parc)
{
	t_parc	*node;
	t_parc	*tmp;

	if (!parc)
		return ;
	tmp = *parc;
	while (tmp)
	{
		free(tmp->cmd);
		free(tmp->hdoc);
		ft_free_args(&tmp->args);
		ft_free_redirs(&tmp->redirs_in);
		ft_free_redirs(&tmp->redirs_out);
		node = tmp->next;
		free(tmp);
		tmp = node;
	}
	*parc = NULL;
}

void	freeall(t_env **env, t_parc **parc)
{
	ft_free_env(env);
	ft_free_parc(parc);
}
