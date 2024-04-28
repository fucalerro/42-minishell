#include "minishell.h"

void	free_lst(t_node *lst)
{
	t_node	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		if (tmp->cmd)
			free_2starchar(tmp->cmd);
		if (tmp->file)
			free(tmp->file);
		if (tmp->delimiter)
			free(tmp->delimiter);
		free(tmp);
	}
}
