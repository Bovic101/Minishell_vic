/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:30:32 by kdvarako          #+#    #+#             */
/*   Updated: 2024/09/23 17:01:44 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
Function heredoc
*/
char	*ft_hdoc(char *s_end)
{
	char	*value;
	char	*s;

	s = NULL;
	value = NULL;
	value = malloc(1);
	if (!value)
		return (NULL);
	value[0] = '\0';
	while (1)
	{
		s = readline("> ");
		if (s != NULL)
		{
			if (ft_strcmp(s, s_end) != 0)
			{
				//if (ft_strlen(value) != 0)
					//value = ft_wordjoin(value, "\n");
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

char	*save_last_hdoc(t_parc *node)
{
	t_redirect	*r_in;
	char		*value;

	value = NULL;
	r_in = node->redirs_in;
	while (r_in)
	{
		if (ft_strcmp(r_in->rtype, "<<") == 0)
		{
			if (value != NULL)
				free(value);
			value = ft_hdoc(r_in->rfile);
			//printf("hdoc: %s |\n", value);
		}
		r_in = r_in->next;
	}
	return (value);
}

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

int redir_in_file(t_parc *node)
{
	t_redirect  *r_in;
	int         fd_file;
	int         err_close;

	r_in = node->redirs_in;
	while (r_in)
	{
		if (ft_strcmp(r_in->rtype, "<") == 0)
		{
			fd_file = open(r_in->rfile, O_RDONLY, 0664);
			if (fd_file == -1)
			{
				printf("no such file or directory: filename\n");
				return (-1); //err handling
			}
			if (r_in->next == NULL)
				dup2(fd_file, 0);
			err_close = close(fd_file);
			if (err_close == -1)
			{
				printf("Error to close\n");
				return (-1); //err handling
			}
		}
		r_in = r_in->next;
	}
	return (0);
}


int	redir_in(t_parc *node)
{
	char		*hdoc;
	t_redirect	*last;

	hdoc = save_last_hdoc(node);
	//printf("%s", hdoc);
	//printf("|\n");
	last = ft_redir_last(node->redirs_in);
	//printf("last type: %s\n", last->rtype);
	if (ft_strcmp(last->rtype, "<<") == 0)
	{
		redir_in_hdoc(hdoc);
		free(hdoc);
	}
	else
		free(hdoc);
	if (redir_in_file(node) == -1)
		return (-1);
	return (0);
}
