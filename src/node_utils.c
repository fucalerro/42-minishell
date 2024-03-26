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

void	lst_append(t_node **lst, int type, char *file, char **cmd)
{
	t_node	*list;
	t_node	*new;

	new = lst_new(type, file, cmd);
	if (*lst)
	{
		list = lst_last(*lst);
		list->next = new;
		new->previous = list;
	}
	else
		*lst = new;
}

void	print_list(t_node *lst)
{
	t_node	*list;

	char *type_table[] = {"T_PIPE", "T_INFILE", "T_OUTFILE", "T_OUTFILE_APPEND", "T_HEREDOC", "T_CMD"};
	int i_node = 0;
	list = lst;
	while (list)
	{
		printf("\nNODE %i\n",i_node++);
		printf("\tnode.type: %s\n", type_table[list->type - 1]);
		printf("\tnode.file: %s\n", list->file);
		if (list->cmd)
		{
			printf("\tnode.cmd: [");
			for (int i = 0; list->cmd[i]; i++)
				printf("\"%s\",", list->cmd[i]);
			printf("]\n");
		}
		else
			printf("\tnode.cmd: (null)\n");
		list = list->next;
	}
}


/*
void main(void)
{
	t_node *lst;

	lst = NULL;

	lst_append(&lst, 0, NULL, NULL);
	lst_append(&lst, 0, NULL, NULL);
	lst_append(&lst, 0, NULL, NULL);
	lst_append(&lst, 0, NULL, NULL);
}
*/
