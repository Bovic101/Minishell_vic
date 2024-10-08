/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 15:00:04 by kdvarako          #+#    #+#             */
/*   Updated: 2024/10/08 03:28:27 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redirect	*ft_redir_new(char *rtype, char *rfile)
{
	t_redirect	*a;

	a = malloc(sizeof(t_redirect));
	if (a == NULL)
		return (NULL);
	a->rtype = rtype;
	a->rfile = rfile;
	a->next = NULL;
	return (a);
}

t_redirect	*ft_redir_last(t_redirect *r)
{
	t_redirect	*ptr;

	if (r == NULL)
		return (NULL);
	ptr = r;
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
	}
	return (ptr);
}

void	ft_redir_add_back(t_redirect **lst, t_redirect *new)
{
	t_redirect	*last;

	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = ft_redir_last(*lst);
	last->next = new;
}

void	add_redir(char *rtype, char *rfile, t_redirect **redirs)
{
	t_redirect	*new;

	new = ft_redir_new(rtype, rfile);
	ft_redir_add_back(redirs, new);
}

void	ft_redir_print(t_redirect **redirs)
{
	t_redirect	*node;

	node = *redirs;
	while (node)
	{
		printf("%s ", node->rtype);
		printf("%s\n", node->rfile);
		node = node->next;
	}
}
