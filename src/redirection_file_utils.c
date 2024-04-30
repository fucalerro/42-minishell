/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_file_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Lu-ni <lucas.nicollier@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:12:43 by Lu-ni             #+#    #+#             */
/*   Updated: 2024/04/28 22:12:43 by Lu-ni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_outfile(t_node *node_tmp, t_node *node)
{
	int	return_value;

	return_value = 0;
	while (node_tmp && node_tmp->type != T_PIPE)
	{
		if (node_tmp->type == T_CMD && node_tmp != node)
			break ;
		else if (node_tmp->type == T_OUTFILE)
			return_value = exe_outfile(node_tmp);
		else if (node_tmp->type == T_OUTFILE_APPEND)
			return_value = exe_outfile_append(node_tmp);
		if (return_value)
			return (return_value);
		node_tmp = node_tmp->next;
	}
	return (return_value);
}

int	run_redirection_file(t_node *node)
{
	t_node	*node_tmp;
	int		return_value;
	t_node	*node_save;

	node_tmp = node;
	return_value = 0;
	while (node_tmp && node_tmp->previous && node_tmp->previous->type != T_PIPE)
		node_tmp = node_tmp->previous;
	node_save = node_tmp;
	while (node_tmp && node_tmp->type != T_PIPE)
	{
		if (node_tmp->type == T_CMD && node_tmp != node)
			return (0);
		else if (node_tmp->type == T_INFILE)
			return_value = exe_infile(node_tmp);
		else if (node_tmp->type == T_HEREDOC)
			return_value = exe_heredoc(node_tmp);
		if (return_value)
			return (return_value);
		node_tmp = node_tmp->next;
	}
	return_value = run_outfile(node_save, node);
	return (return_value);
}
