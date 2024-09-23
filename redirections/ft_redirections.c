/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:33:30 by kdvarako          #+#    #+#             */
/*   Updated: 2024/09/23 15:56:55 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_redirections(t_parc **parc)
{
	t_parc	*node;
	int		ret_inr;

	//<< && <
	node = *parc;
	ret_inr = 0;
	while (node)
	{
		if (node->redirs_in != NULL)
		{
			ret_inr = redir_in(node);
		}
		node = node->next;
	}
	//printf("ret_inr = %d\n", ret_inr);
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
	if (ret_inr == -1)
		return (-1);
	return (0);
}
