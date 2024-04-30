/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolli <lnicolli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:12:43 by Lu-ni             #+#    #+#             */
/*   Updated: 2024/04/30 20:32:56 by lnicolli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_err(char *str)
{
	int	size;

	size = ft_strlen(str);
	write(2, str, size);
}

int	check_error(t_node *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		if (lst->type == T_HEREDOC)
			i++;
		if (i > 1)
		{
			write_err("too much heredoc\n");
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}

void	ft_dup2(int fd1, int fd2)
{
	if (dup2(fd1, fd2) < 0)
		exit(EXIT_FAILURE);
}
