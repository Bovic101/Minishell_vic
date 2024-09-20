/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:21:47 by kdvarako          #+#    #+#             */
/*   Updated: 2024/09/20 13:06:01 by kdvarako         ###   ########.fr       */
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

int redir_out(t_parc *node)
{
	t_redirect  *r_out;
	int         fd_file;
	int         err_close;

	r_out = node->redirs_out;
	while (r_out)
	{
		printf("%s\n", r_out->rtype);
		if (ft_strcmp(r_out->rtype, ">>"))
			fd_file = open(r_out->rfile, O_APPEND | O_CREAT | O_RDWR, 0664);
		else
			fd_file = open(r_out->rfile, O_CREAT | O_RDWR | O_TRUNC, 0664);
		if (fd_file == -1)
		{
			printf("Error to open file\n");
			return (-1); //err handling
		}
		if (r_out->next == NULL)
		{
			dup2(fd_file, 1);
			err_close = close(fd_file);
			if(err_close == -1)
			{
				printf("Error to close file\n");
				return (-1); //err handling
			}
		}
		else
		{
			err_close = close(fd_file);
			if(err_close == -1)
			{
				printf("Error to close file\n");
				return (-1); //err handling
			}
		}
		r_out = r_out->next;
	}
	return (0);
}

int	ft_redirections(t_parc **parc)
{
	t_parc	*node;

	//<< && <
	node = *parc;
	while (node)
	{
		/*if (node->redirs_in != NULL)
		{
		}*/
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