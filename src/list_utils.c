#include "minishell.h"

int sort_infile(t_node **lst)
{
	t_node *node;
	t_node *node_prev;
	t_node *node_next;
	t_node *node_next2;

	node = *lst;

	while(node)
	{
		if (node->next && node->type == T_CMD && node->next->type == T_INFILE)
		{
			node_next = node->next;
			node_next2 = node->next->next;
			node_prev = node->previous;
			
			node->next = node_next2;
			node->previous = node_next;
			if(node_next2)
				node_next2->previous = node;

			node_next->next = node;
			node_next->previous = node_prev;
			if (node_prev)
			{
				node_prev->next = node_next ;
			}
			else
			{
				*lst = node_next;
			}
		}
		node = node->next;
	}
}
