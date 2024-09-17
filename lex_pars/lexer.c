/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:02:58 by kdvarako          #+#    #+#             */
/*   Updated: 2024/09/17 13:16:25 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lexer(t_token **token, char *s)
{
	t_token				*new;
	int					i;
	int					len;
	enum e_tokentype	type;
	char				*ptr;
	int					fl;

	if (s == NULL)
		return ;
	//save_history(s, history);
	//ft_history_print(history);
	i = 0;
	ptr = NULL;
	while (s[i] != '\0' && (s[i] == ' ' || s[i] == '\t'))
		i++;
	while (s[i] != '\0')
	{
		ptr = &s[i];
		len = 0;
		if (s[i] == '<')
		{
			if (s[i + 1] == '<')
			{
				len++;
				i++;
				type = REDIR_IN2;
			}
			else
				type = REDIR_IN;
			len++;
			i++;
		}
		else if (s[i] == '>')
		{
			if (s[i + 1] == '>')
			{
				len++;
				i++;
				type = REDIR_OUT2;
			}
			else
				type = REDIR_OUT;
			len++;
			i++;
		}
		else if (s[i] == '|')
		{
			type = PIPE;
			len++;
			i++;
		}
		else if (s[i] == ' ')
		{
			while (s[i] == ' ')
			{
				i++;
				len++;
			}
			type = SEPARATOR;
		}
		else if (s[i] == 34) //double quotes = 34
		{
			i++;
			fl = 0;
			ptr = &s[i];
			while (s[i] != 34)
			{
				if (s[i] == '$')
					fl = 1;
				i++;
				len++;
			}
			type = WORD;
			if (fl == 1)
				type = EXPAND_VAR_Q;
			i++;
		}
		else if (s[i] == 39) //single quotes = 39
		{
			i++;
			ptr = &s[i];
			while (s[i] != 39)
			{
				i++;
				len++;
			}
			type = WORD;
			i++;
		}
		else
		{
			fl = 0;
			while (s[i] != '\0' && s[i] != ' ' && s[i] != 34 && s[i] != 39 \
				&& s[i] != '|')
			{
				if (s[i] == '$')
					fl = 1;
				len++;
				i++;
			}
			type = WORD;
			if (fl == 1)
				type = EXPAND_VAR;
		}
		new = ft_lst_new(len, ptr, type);
		ft_lst_add_back(token, new);
	}
}
