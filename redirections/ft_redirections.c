/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:33:30 by kdvarako          #+#    #+#             */
/*   Updated: 2024/09/26 12:36:50 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
//<< && <
int	redirections_in(t_parc **parc)
{
	t_parc		*node;
	t_redirect	*r_in;
	char		*value;
	t_redirect	*last;

	value = NULL;
	node = *parc;
	while (node)
	{
		if (node->redirs_in != NULL)
		{
			r_in = node->redirs_in;
			while (r_in)
			{
				if (ft_strcmp(r_in->rtype, "<<") == 0)
				{
					if (value != NULL)
						free(value);
					value = ft_hdoc(r_in->rfile);
				}
				r_in = r_in->next;
			}
		}
		node = node->next;
	}
	//printf("hdoc: %s|\n", value);
	node = *parc;
	while (node)
	{
		if (node->redirs_in != NULL)
		{
			redir_in_file(node);
		}
		node = node->next;
	}
	last = ft_redir_last(ft_plst_last(*parc)->redirs_in);
	if (last != NULL && (ft_strcmp(last->rtype, "<<") == 0))
	{
		redir_in_hdoc(value);
		free(value);
	}
	else
		free(value);
	return (0);
}

//>> && >
int	redirections_out(t_parc **parc)
{
	t_parc	*node;

	node = *parc;
	while (node)
	{
		if (node->redirs_out != NULL)
		{
			redir_out(node);
		}
		node = node->next;
	}
	return (0);
}
*/
int	ft_redirections(t_parc *node)
{
	//int		ret_inr;

	//<< && <
	//ret_inr = 0;
	if (node->redirs_in != NULL)
	{
		redir_in(node);
	}
	//>> && >
	if (node->redirs_out != NULL)
	{
		redir_out(node);
	}
	return (0);
}
