/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:30:32 by kdvarako          #+#    #+#             */
/*   Updated: 2024/09/30 10:34:50 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int redir_in_hdoc(char *hdoc)
{
	int	fd_h[2];
	int	err;

	err = pipe(fd_h);
	if (err < 0)
		return (-1);  //err handling
	if (write(fd_h[1], hdoc, ft_strlen(hdoc) + 1) < 0)
			return (-1);  //err handling
	dup2(fd_h[0], 0);
	close(fd_h[0]);
	close(fd_h[1]);
	return (0);
}

int redir_in(t_parc *node)
{
	t_redirect  *r_in;
	int         fd_file;
	//int         err_close;

	r_in = node->redirs_in;
	while (r_in)
	{
		if (ft_strcmp(r_in->rtype, "<") == 0)
		{
			fd_file = open(r_in->rfile, O_RDONLY, 0664);
			if (fd_file == -1)
			{
				write(2, "no such file or directory\n", 26); //err print
				return (-1); //err handling
			}
			if (r_in->next == NULL)
				dup2(fd_file, 0);
			close(fd_file);
			/*if (err_close == -1)
			{
				printf("Error to close\n");
				return (-1); //err handling
			}*/
		}
		else
		{
			if (r_in->next == NULL)
				redir_in_hdoc(node->hdoc);
			//+err handler
		}
		r_in = r_in->next;
	}
	return (0);
}


