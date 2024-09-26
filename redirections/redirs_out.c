/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:31:15 by kdvarako          #+#    #+#             */
/*   Updated: 2024/09/26 11:40:18 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int redir_out(t_parc *node)
{
	t_redirect  *r_out;
	int         fd_file;
	int         err_close;

	r_out = node->redirs_out;
	while (r_out)
	{
		if (ft_strcmp(r_out->rtype, ">>") == 0)
			fd_file = open(r_out->rfile, O_APPEND | O_CREAT | O_RDWR, 0664);
		else
			fd_file = open(r_out->rfile, O_CREAT | O_RDWR | O_TRUNC, 0664);
		if (fd_file == -1)
		{
			printf("Error to open file\n");
			return (-1); //err handling
		}
		if (r_out->next == NULL)
			dup2(fd_file, 1);
		err_close = close(fd_file);
		if (err_close == -1)
		{
			printf("Error to close file\n");
			return (-1); //err handling
		}
		r_out = r_out->next;
	}
	return (0);
}
