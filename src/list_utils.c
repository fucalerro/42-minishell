#include "minishell.h"

int	switch_node_n_node_next(t_node **lst, t_node *node)
{
	t_node	*node_prev;
	t_node	*node_next;
	t_node	*node_next2;

	if (node->next)
	{
		node_next = node->next;
		node_next2 = node->next->next;
		node_prev = node->previous;
		node->next = node_next2;
		node->previous = node_next;
		if (node_next2)
			node_next2->previous = node;
		node_next->next = node;
		node_next->previous = node_prev;
		if (node_prev)
			node_prev->next = node_next;
		else
			*lst = node_next;
	}
	return (0);
}
int	correct_order(t_node *node)
{
	if (node->next && (node->type > node->next->type) && node->type != T_PIPE
		&& node->next->type != T_PIPE)
	{
		if (node->type >= T_CMD && node->next->type <= T_CMD)
			return (1);
		if (node->type <= T_CMD && node->next->type >= T_CMD)
			return (1);
	}
	return (0);
}
int	sort_infile(t_node **lst)
{
	t_node	*node;
	t_node	*node_prev;
	t_node	*node_next;
	t_node	*node_next2;

	node = *lst;
	while (node)
	{
		if (correct_order(node))
		{
			switch_node_n_node_next(lst, node);
			node = *lst;
		}
		else
			node = node->next;
	}
	return (0);
}
