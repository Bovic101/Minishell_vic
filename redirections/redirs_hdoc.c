/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_hdoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 20:48:49 by vodebunm          #+#    #+#             */
/*   Updated: 2024/10/08 03:30:14 by vodebunm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
starts heredoc
*/
char	*ft_hdoc(char *s_end, char *value)
{
	char	*s;

	s = NULL;
	while (1)
	{
		s = readline("> ");
		if (s != NULL)
		{
			if (ft_strcmp(s, s_end) != 0)
			{
				value = ft_wordjoin(value, s);
				value = ft_wordjoin(value, "\n");
				free(s);
			}
			else
			{
				free(s);
				break ;
			}
		}
	}
	return (value);
}

/*
goes through all redirections << in node,
	starts heredoc and returns the last one
*/
char	*save_last_hdoc(t_parc *node)
{
	t_redirect	*r_in;
	char		*value;
	char		*val;

	value = NULL;
	r_in = node->redirs_in;
	while (r_in)
	{
		if (ft_strcmp(r_in->rtype, "<<") == 0)
		{
			if (value != NULL)
				free(value);
			val = NULL;
			val = malloc(1);
			if (!val)
				value = NULL;
			else
			{
				val[0] = '\0';
				value = ft_hdoc(r_in->rfile, val);
			}
		}
		r_in = r_in->next;
	}
	return (value);
}

int	save_all_hdoc(t_parc **parc)
{
	t_parc	*node;

	node = *parc;
	while (node)
	{
		if (node->redirs_in != NULL)
			node->hdoc = save_last_hdoc(node);
		else
			node->hdoc = NULL;
		node = node->next;
	}
	return (0);
}
