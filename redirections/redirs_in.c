/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vodebunm <vodebunm@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:30:32 by kdvarako          #+#    #+#             */
/*   Updated: 2024/09/20 22:17:17 by vodebunm         ###   ########.fr       */
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
				if (ft_strlen(value) != 0)
					value = ft_wordjoin(value, "\n");
				value = ft_wordjoin(value, s);
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
		}
		r_in = r_in->next;
	}
	return (value);
}

int redir_in(t_parc *node)
{
	t_redirect  *r_in;
	int         fd_file;
	int         err_close;
	//char		*hdoc;

	//hdoc = save_last_hdoc(node);
	//printf("%s", hdoc);
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
				printf("Error to close file\n");
				return (-1); //err handling
			}
		}
		r_in = r_in->next;
	}
	//free hdoc if not NULL
	return (0);
}
