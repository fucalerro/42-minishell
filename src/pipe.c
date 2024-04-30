/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Lu-ni <lucas.nicollier@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:12:43 by Lu-ni             #+#    #+#             */
/*   Updated: 2024/04/28 22:16:33 by bob              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "node.h"

int	init_pipe(t_node *node)
{
	while (node)
	{
		if (node->type == T_PIPE && node->active)
			pipe(node->pipe);
		node = node->next;
	}
	return (0);
}

int	close_pipe(t_node *node)
{
	while (node && node->previous)
		node = node->previous;
	while (node)
	{
		if (node->type == T_PIPE && node->active)
		{
			close(node->pipe[0]);
			close(node->pipe[1]);
		}
		node = node->next;
	}
	return (0);
}

int	stdin_occupied(t_node *node)
{
	while (node && node->previous && node->previous->type != T_PIPE)
		node = node->previous;
	while (node && node->type != T_PIPE)
	{
		if (node->type == T_INFILE || node->type == T_HEREDOC)
			return (1);
		node = node->next;
	}
	return (0);
}

int	set_pipe(t_node *node)
{
	int		check_value;
	t_node	*tmp;

	tmp = node;
	check_value = check_pipe(node);
	if (check_value & PIPE_NEXT)
	{
		while (tmp->type != T_PIPE)
			tmp = tmp->next;
		close(tmp->pipe[0]);
		ft_dup2(tmp->pipe[1], STDOUT_FILENO);
		close(tmp->pipe[1]);
	}
	tmp = node;
	if (check_value & PIPE_PREVIOUS)
	{
		while (tmp->type != T_PIPE)
			tmp = tmp->previous;
		close(tmp->pipe[1]);
		if (!stdin_occupied(node))
			ft_dup2(tmp->pipe[0], STDIN_FILENO);
		close(tmp->pipe[0]);
	}
	return (0);
}

int	check_pipe(t_node *node)
{
	int		return_value;
	t_node	*tmp;

	tmp = node;
	return_value = 0;
	while (tmp && tmp->type != T_PIPE)
		tmp = tmp->next;
	if (tmp && tmp->type == T_PIPE && tmp->active)
		return_value += 1;
	tmp = node;
	while (tmp && tmp->type != T_PIPE)
		tmp = tmp->previous;
	if (tmp && tmp->type == T_PIPE && tmp->active)
		return_value += 2;
	return (return_value);
}
