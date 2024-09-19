#include "../minishell.h"

int redir_out(t_parc *node)
{
    t_redirect  *r_out;
    int         fd_file;
    int         err_close;

    r_out = node->redirs_out;
    while (r_out)
    {
        if (ft_strcmp(r_out->rtype, ">"))
            fd_file = open(r_out->rfile, O_CREAT | O_RDWR, 0664);
        else
            fd_file = open(r_out->rfile, O_CREAT | O_RDWR | O_APPEND, 0664);
        if (fd_file == -1)
        {
            printf("Error to open file\n");
            return (-1); //err handling
        }
        if (r_out->next == NULL)
        {
            dup2(fd_file, 1);
        }
        err_close = close(fd_file);
        if(err_close == -1)
        {
            printf("Error to close file\n");
            return (-1); //err handling
        }
        r_out = r_out->next;
    }
    return (0);
}

int	ft_redirections(t_parc **parc)
{
	t_parc	*node;
	node = *parc;
    while (node)
    {
        /*if (node->redirs_in != NULL)
        {
            //<< && <
        }*/
        if (node->redirs_out != NULL)
        {
            //>> && >
            redir_out(node);
        }
        node = node->next;
    }
    return (0);
}