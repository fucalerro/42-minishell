#include "minishell.h"

// node_create(cmd, special);
// node_remove
// node_insert


char **ft_cmdsdup(char **cmds)
{
	int count;
	char **tmp;

	count = 0;
	while(cmds && cmds[count])
		count++;
	tmp = malloc(sizeof(char *) * (count + 1));
	if (!tmp)
		return NULL;
	count = 0;
	while (cmds && cmds[count])
	{
		tmp[count] = cmds[count];
		if(!tmp[count])
			return NULL;
		count ++;
	}
	tmp[count] = NULL;
	return tmp;
}

t_node	*lst_new(int type, char *file, char **cmd, char *delimiter)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(struct s_node));
	if (!node)
		return ((t_node *)0);
	node->delimiter = ft_strdup(delimiter);
	node->type = type;
	node->active = 1;
	node->file = ft_strdup(file);
	node->cmd = ft_cmdsdup(cmd);
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

void	lst_append(t_node **lst, int type, char *file, char **cmd,
		char *delimiter)
{
	t_node	*list;
	t_node	*new;

	new = lst_new(type, file, cmd, delimiter);
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
	char	*type_table[] = {"T_PIPE", "T_INFILE", "T_HEREDOC", "T_CMD", "T_OUTFILE",
		"T_OUTFILE_APPEND"};
	int		i_node;

	i_node = 0;
	list = lst;
	while (list)
	{
		printf("\nNODE %i\n", i_node++);
		printf("\tnode.type: %s\n", type_table[list->type - 1]);
		printf("\tnode.active: %i\n", list->active);
		printf("\tnode.file: %s\n", list->file);
		printf("\tnode.delimiter: %s\n", list->delimiter);
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

void	free_lst(t_node *lst)
{
	t_node	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		if (tmp->cmd)
			free_2starchar(tmp->cmd);
		free(tmp);
	}
}
