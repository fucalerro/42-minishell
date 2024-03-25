#include "minishell.h"
// node_create(cmd, special);
// node_remove
// node_insert


t_node	*lst_new(int type, char *file, char **cmd)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(struct s_node));
	if (!node)
		return ((t_node *)0);
	node->type = type;
	node->file = file;
	node->cmd = cmd; // I think we should have commands an array ["cmd name", "cmd args"]
	node->previous = (t_node *)0;
	node->next = (t_node *)0;
	return (node);
}

t_node	*lst_last(t_node *lst)
{
	if (!lst)
		return ((t_node *)0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	lst_append(t_node **lst, t_node *new)
{
	t_node	*list;

	if (*lst)
	{
		list = lst_last(*lst);
		list->next = new;
		new->previous = list;
	}
	else
		*lst = new;
}
/*
void main(void)
{
	t_node *lst;
	t_node *node;
	t_node *node1;
	t_node *node2;
	t_node *node3;

	lst = NULL;
	node = lst_new(0, NULL, NULL);
	node1 = lst_new(0, NULL, NULL);
	node2 = lst_new(0, NULL, NULL);
	node3 = lst_new(0, NULL, NULL);
	lst_append(&lst, node);
	lst_append(&lst, node2);
	lst_append(&lst, node3);
	lst_append(&lst, node1);
}*/
