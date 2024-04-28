#include "minishell.h"

static char	**ft_cmdsdup(char **cmds)
{
	int		count;
	char	**tmp;

	if (!cmds)
		return (NULL);
	count = 0;
	while (cmds && cmds[count])
		count++;
	tmp = malloc(sizeof(char *) * (count + 1));
	if (!tmp)
		return (NULL);
	count = 0;
	while (cmds && cmds[count])
	{
		tmp[count] = ft_strdup(cmds[count]);
		if (!tmp[count])
			return (NULL);
		count++;
	}
	tmp[count] = NULL;
	return (tmp);
}

static t_node	*lst_new(int type, char *file, char **cmd, char *delimiter)
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

static t_node	*lst_last(t_node *lst)
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
