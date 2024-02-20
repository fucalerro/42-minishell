/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 12:31:37 by lferro            #+#    #+#             */
/*   Updated: 2023/10/17 13:44:19 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next != 0)
		current = current->next;
	current->next = new;
}

// void	ft_lstadd_back(t_list **lst, t_list *new)
// {
// 	if (*lst == NULL)
// 		*lst = new;
// 	else if ((*lst)->next == NULL)
// 		(*lst)->next = new;
// 	else
// 		ft_lstadd_back(&(*lst)->next, new);
// }