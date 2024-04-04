#include "minishell.h"

int switch_node_n_node_next(t_node **lst, t_node *node)
{
	t_node *node_prev;
	t_node *node_next;
	t_node *node_next2;

	if (node->next)
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
			node_prev->next = node_next ;
		else
			*lst = node_next;
	}
	return (0);
}

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
			switch_node_n_node_next(lst, node);
		else
			node = node->next;
	}
	return (0);
}
//	0 -> last pipe (if not = start of list)
//	1 -> infile
//	2 -> here doc
//	3 -> cmd
//	4 -> outfile
//	5 -> outfile append
//	6 -> next pipe (if not = end of list)
void sort_prompt(t_node **lst)
{
	t_node *node = *lst;


	if(!lst)
		return;

}
