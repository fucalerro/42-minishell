/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 12:10:39 by lferro            #+#    #+#             */
/*   Updated: 2023/10/17 13:44:23 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*new_elem;

	if (!(lst && f && del))
		return (NULL);
	newlst = ft_lstnew(f(lst->content));
	if (!newlst)
		return (NULL);
	lst = lst->next;
	while (lst)
	{
		new_elem = ft_lstnew(f(lst->content));
		if (new_elem == 0)
		{
			ft_lstclear(&newlst, del);
			return (NULL);
		}
		ft_lstadd_back(&newlst, new_elem);
		lst = lst->next;
	}
	return (newlst);
}

// t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
// {
// 	t_list	*new_lst;
// 	t_list	*new_node;
// 	void	*new_content;

// 	if (lst == NULL)
// 		return (NULL);
// 	while (lst)
// 	{
// 		new_content = f(lst->content);
// 		new_node = ft_lstnew(new_content);
// 		if (new_node == NULL)
// 		{
// 			free(new_content);
// 			ft_lstclear(&new_node, del);
// 			return (NULL);
// 		}
// 		ft_lstadd_back(&new_lst, new_node);
// 		lst = lst->next;
// 	}
// 	return (new_lst);
// }
