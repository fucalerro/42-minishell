/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:11:40 by lferro            #+#    #+#             */
/*   Updated: 2023/10/17 13:44:21 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*next;

	current = *lst;
	while (current != NULL)
	{
		next = current->next;
		del(current->content);
		free(current);
		current = next;
	}
	*lst = NULL;
}

// // delete an INT item
// void	lst_delete(void *nbr)
// {
// 	// free(nbr);
// }

// int	main(void)
// {
// 	int		n1;
// 	int		n2;
// 	int		n3;
// 	int		n4;
// 	int		n5;
// 	t_list	*node_n1;
// 	t_list	*node_n2;
// 	t_list	*node_n3;
// 	t_list	*node_n4;
// 	t_list	*node_n5;

// 	n1 = 1;
// 	n2 = 2;
// 	n3 = 3;
// 	n4 = 4;
// 	n5 = 5;
// 	node_n1 = ft_lstnew(&n1);
// 	node_n2 = ft_lstnew(&n2);
// 	node_n3 = ft_lstnew(&n3);
// 	node_n4 = ft_lstnew(&n4);
// 	node_n5 = ft_lstnew(&n5);
// 	ft_lstadd_front(&node_n1, node_n2);
// 	ft_lstadd_front(&node_n1, node_n3);
// 	ft_lstadd_front(&node_n1, node_n4);
// 	ft_lstadd_front(&node_n1, node_n5);
// 	ft_lstclear(&node_n3, lst_delete);
// 	return (0);
// }
