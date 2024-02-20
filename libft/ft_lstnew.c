/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 20:20:29 by lferro            #+#    #+#             */
/*   Updated: 2023/10/17 13:44:24 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

// int main(void)
// {
// 	int nbr = 12;
// 	t_list *int_item = ft_lstnew(&nbr);
// 	char *str = "hello";
// 	t_list *str_item = ft_lstnew(str);
// 	printf("%d\n", *(int *)int_item->content);
// 	printf("%s\n", (char *)str_item->content);
// 	return (0);
// }
