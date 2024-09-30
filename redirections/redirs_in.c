/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:30:32 by kdvarako          #+#    #+#             */
/*   Updated: 2024/09/30 15:08:50 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir_in_hdoc(char *hdoc)
{
	int	fd_h[2];
	int	err;

	err = pipe(fd_h);
	if (err < 0)
	{
		print_error_msg(NULL, NULL, "Pipe error");
		return (-1);
	}
	if (write(fd_h[1], hdoc, ft_strlen(hdoc) + 1) < 0)
	{
		print_error_msg(NULL, NULL, "Write error");
		return (-1);
	}
	dup2(fd_h[0], 0);
	close(fd_h[0]);
	close(fd_h[1]);
	return (0);
}

int redir_in(t_parc *node)
{
	t_redirect	*r_in;
	int			fd_file;

	r_in = node->redirs_in;
	while (r_in)
	{
		if (ft_strcmp(r_in->rtype, "<") == 0)
		{
			fd_file = open(r_in->rfile, O_RDONLY, 0664);
			if (fd_file == -1)
			{
				print_error_msg(NULL, r_in->rfile, "No such file or directory");
				return (1);
			}
			if (r_in->next == NULL)
				dup2(fd_file, 0);
			close(fd_file);
		}
		else
		{
			if (r_in->next == NULL)
			{
				if (redir_in_hdoc(node->hdoc) == -1)
					return (-1);
			}
		}
		r_in = r_in->next;
	}
	return (0);
}


