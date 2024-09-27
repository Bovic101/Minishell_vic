
#include "../minishell.h"

/*
starts heredoc
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

/*
goes through all redirections << in node, starts heredoc and returns the last one
*/
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

/*
    redirections <<
    saves all last hdoc for every node in node->hdoc (structutr parc)
    if there is no <<, saves NULL
*/
int	save_all_hdoc(t_parc **parc)
{
	t_parc		*node;

	node = *parc;
	while (node)
	{
		if (node->redirs_in != NULL)
            node->hdoc = save_last_hdoc(node);
        else
            node->hdoc = NULL;
		node = node->next;
	}
    return (0);
}