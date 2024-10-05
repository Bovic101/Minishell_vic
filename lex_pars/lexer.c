/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdvarako <kdvarako@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:02:58 by kdvarako          #+#    #+#             */
/*   Updated: 2024/10/05 17:29:37 by kdvarako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lexer_pipe(int *i, int *len, enum e_tokentype *type)
{
	*type = PIPE;
	(*len)++;
	(*i)++;
}

void	lexer_separator(char *s, int *i, int *len, enum e_tokentype *type)
{
	while (s[*i] == ' ')
	{
		(*len)++;
		(*i)++;
	}
	*type = SEPARATOR;
}

/*
34 - double quotes
39 - single quotes
*/
t_token	*lexer_new_token(char *s, int *i)
{
	int					len;
	enum e_tokentype	type;
	char				*ptr;
	t_token				*new;

	ptr = NULL;
	ptr = &s[*i];
	len = 0;
	if (s[*i] == '<')
		lexer_redir_in(s, i, &len, &type);
	else if (s[*i] == '>')
		lexer_redir_out(s, i, &len, &type);
	else if (s[*i] == '|')
		lexer_pipe(i, &len, &type);
	else if (s[*i] == ' ')
		lexer_separator(s, i, &len, &type);
	else if (s[*i] == 34)
		ptr = lexer_double_quotes(s, i, &len, &type);
	else if (s[*i] == 39)
		ptr = lexer_single_quotes(s, i, &len, &type);
	else
		lexer_word(s, i, &len, &type);
	new = ft_lst_new(len, ptr, type);
	return (new);
}

void	lexer(t_token **token, char *s)
{
	t_token				*new;
	int					i;


	if (s == NULL)
		return ;
	i = 0;
	while (s[i] != '\0' && (s[i] == ' ' || s[i] == '\t'))
		i++;
	while (s[i] != '\0')
	{
		new = lexer_new_token(s, &i);
		ft_lst_add_back(token, new);
	}
}
