/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolli <lnicolli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:12:43 by Lu-ni             #+#    #+#             */
/*   Updated: 2024/04/29 14:59:34 by lnicolli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	tmp = palloc(count + 1, sizeof(char *));
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

	node = (t_node *)palloc(1, sizeof(struct s_node));
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

char **merge_str(char *file, char *del)
{
	char **merge;
	merge = palloc(2, sizeof(char *));
	if (!merge)
		return NULL;
	merge[0] = file;
	merge[1] = del;
	return (merge);
}

void	lst_append(t_node **lst, int type, char **cmd, char *arg[2])
{
	t_node	*list;
	t_node	*new;

	new = lst_new(type, arg[0], cmd, arg[1]);
	if (*lst)
	{
		list = lst_last(*lst);
		list->next = new;
		new->previous = list;
	}
	else
		*lst = new;
	free(arg);
}
