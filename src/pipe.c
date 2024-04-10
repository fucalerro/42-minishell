#include "minishell.h"
void check_pipe_status(t_node *node)
{
	t_node *tmp = node;

	while(node)
	{
		if(node->type == T_PIPE)
		{
			tmp = node->next;
			while(tmp && node->active && tmp->type != T_PIPE)
			{
				if(tmp->type == T_INFILE ||tmp->type == T_HEREDOC)
					node->active = 0;
				tmp = tmp->next;
			}
			tmp = node->previous;
			while(tmp && node->active && tmp->type != T_PIPE)
			{
				if(tmp->type == T_OUTFILE ||tmp->type == T_OUTFILE_APPEND)
					node->active = 0;
				tmp = tmp->previous;
			}
		}

		node = node->next;
	}
}
