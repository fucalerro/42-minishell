/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:54:48 by lferro            #+#    #+#             */
/*   Updated: 2023/10/17 13:44:23 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

// int main(void)
// {
// 	int n1 = 12;
// 	int n2 = 34;
// 	int n3 = 56;
// 	int n4 = 78;
// 	int n5 = 90;
// 	t_list *node_n1 = ft_lstnew(&n1);
// 	t_list *node_n2 = ft_lstnew(&n2);
// 	t_list *node_n3 = ft_lstnew(&n3);
// 	t_list *node_n4 = ft_lstnew(&n4);
// 	t_list *node_n5 = ft_lstnew(&n5);
// 	ft_lstadd_back(&node_n1, node_n2);
// 	ft_lstadd_back(&node_n1, node_n3);
// 	ft_lstadd_back(&node_n1, node_n4);
// 	ft_lstadd_back(&node_n1, node_n5);
// 	printf("%d", *(int *)(ft_lstlast(node_n1)->content));
// 	return (0);
// }
