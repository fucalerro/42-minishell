#include "minishell.h"


int access_infile(char *filepath)
{
    if (access(filepath, F_OK) == -1)
    {
        printf("minishell: %s: No such file or directory\n", filepath);
        return (1);
    }
    if (access(filepath, R_OK) == -1)
    {
        printf("minishell: %s: Permission denied\n", filepath);
        return (1);
    }
    return (0);
}

int	access_outfile(const char *filename)
{
	if (open(filename, O_DIRECTORY) >= 0)
    {
        printf("minishell: %s: Is a directory\n", filename);
        return (1);
    }
	if (access(filename, F_OK) == -1)
    {
		if (access(".", W_OK) == -1)
        {
            printf("minishell: %s: Permission denied\n", filename);
            return (1);
        }
    }
	else if (access(filename, W_OK) == -1)
    {
        printf("minishell: %s: Permission denied\n", filename);
        return (1);
    }
    return (0);
}

int    parsing_error(t_node **lst)
{
    t_node *tmp;

    tmp = *lst;
    while (tmp)
    {
        if (tmp->type == T_CMD)
        {
            if (tmp->next->type == T_CMD && tmp->next)
            {
                error;
            }
        }
        if (tmp->type == T_PIPE)
        {
            if (tmp->next == NULL)
            {
                error;
            }
            if (tmp->next->type == T_PIPE && tmp->next)
            {
                error;
            }

        }
        tmp = tmp->next;
    }
    return (0);



}
