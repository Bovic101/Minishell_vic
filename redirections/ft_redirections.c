/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:33:30 by kdvarako          #+#    #+#             */
/*   Updated: 2024/09/20 16:33:34 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_redirections(t_parc **parc)
{
	t_parc	*node;

	//<< && <
	node = *parc;
	while (node)
	{
		if (node->redirs_in != NULL)
		{
			redir_in(node);
		}
		node = node->next;
	}
	//>> && >
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
