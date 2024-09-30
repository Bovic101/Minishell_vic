/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:33:30 by kdvarako          #+#    #+#             */
/*   Updated: 2024/09/30 14:56:54 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_redirections(t_parc *node)
{
	//int	return_in;
	//int	return_out;

	//<< && <
	if (node->redirs_in != NULL)
	{
		if (redir_in(node) != 0)
			return (1);
	}
	//>> && >
	if (node->redirs_out != NULL)
	{
		redir_out(node);
	}
	return (0);
}
