/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 09:11:35 by lferro            #+#    #+#             */
/*   Updated: 2023/10/17 13:44:22 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst != NULL)
	{
		f(lst->content);
		lst = lst->next;
	}
}

// // printf with correct signature for ft_lstiter
// void print_content(void *content)
// {
//     int *data = (int *)content;
//     printf("%d\n", *data);
// }
// int main(int argc, char const *argv[])
// {
// 	int n1 = 1;
// 	int n2 = 2;
// 	int n3 = 3;
// 	t_list *node_n1 = ft_lstnew(&n1);
// 	t_list *node_n2 = ft_lstnew(&n2);
// 	t_list *node_n3 = ft_lstnew(&n3);
// 	ft_lstadd_back(&node_n1, node_n2);
// 	ft_lstadd_back(&node_n1, node_n3);
// 	ft_lstiter(node_n1, print_content);
// 	return (0);
