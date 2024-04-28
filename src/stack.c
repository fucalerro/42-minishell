/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Lu-ni <lucas.nicollier@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:12:43 by Lu-ni             #+#    #+#             */
/*   Updated: 2024/04/28 22:12:43 by Lu-ni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_stack	*stack_new(int content)
{
	t_stack	*new;

	new = (t_stack *)malloc(sizeof(t_stack));
	if (new == NULL)
		return (NULL);
	new->value = content;
	new->next = NULL;
	return (new);
}

void	stack_add(t_stack **lst, int value)
{
	t_stack	*new;
	t_stack	*node;

	node = *lst;
	new = stack_new(value);
	if (!lst)
		return ;
	if (!node)
	{
		*lst = new;
		return ;
	}
	while (node && node->next)
		node = node->next;
	node->next = new;
}

void	stack_drop(t_stack **lst)
{
	t_stack	*next;

	if (lst && *lst)
	{
		next = (*lst)->next;
		free(*lst);
		*lst = next;
	}
}
