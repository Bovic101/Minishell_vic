/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_parc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:53:35 by kdvarako          #+#    #+#             */
/*   Updated: 2024/10/05 18:06:31 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_parc	*ft_plst_new(char *cmd, t_arg *args, \
	t_redirect *redirs_in, t_redirect *redirs_out)
{
	t_parc	*a;

	a = malloc(sizeof(t_parc));
	if (a == NULL)
		return (NULL);
	a->cmd = cmd;
	a->args = args;
	a->redirs_in = redirs_in;
	a->redirs_out = redirs_out;
	a->next = NULL;
	return (a);
}

t_parc	*ft_plst_last(t_parc *p)
{
	t_parc	*ptr;

	if (p == NULL)
		return (NULL);
	ptr = p;
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
	}
	return (ptr);
}

void	ft_plst_add_back(t_parc **parc, t_parc *new)
{
	t_parc	*last;

	if (new == NULL)
		return ;
	if (*parc == NULL)
	{
		*parc = new;
		return ;
	}
	last = ft_plst_last(*parc);
	last->next = new;
}

void	ft_plst_print(t_parc **parc)
{
	t_parc	*node;

	node = *parc;
	while (node)
	{
		printf("cmd: %s\n", node->cmd);
		printf("args:\n");
		ft_arg_print(&node->args);
		printf("redirs_in:\n");
		ft_redir_print(&node->redirs_in);
		printf("redirs_out:\n");
		ft_redir_print(&node->redirs_out);
		printf("\n");
		node = node->next;
	}
}
