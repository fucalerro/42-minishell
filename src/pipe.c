#include "minishell.h"
#include "node.h"

void	check_pipe_status(t_node *node)
{
	t_node	*tmp;

	tmp = node;
	while (node)
	{
		if (node->type == T_PIPE)
		{
			tmp = node->next;
			while (tmp && node->active && tmp->type != T_PIPE)
			{
				if (tmp->type == T_INFILE || tmp->type == T_HEREDOC)
					node->active = 0;
				tmp = tmp->next;
			}
			tmp = node->previous;
			while (tmp && node->active && tmp->type != T_PIPE)
			{
				if (tmp->type == T_OUTFILE || tmp->type == T_OUTFILE_APPEND)
					node->active = 0;
				tmp = tmp->previous;
			}
		}
		node = node->next;
	}
}

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
int stdin_occupied(t_node *node)
{
	while (node && node->previous && node->previous->type != T_PIPE)
		node = node->previous;
	while (node && node->type != T_PIPE)
	{
		if(node->type == T_INFILE || node->type == T_HEREDOC)
			return(1);
		node = node->next;
	} 
	return(0);
}
int	set_pipe(t_node *node)
{
	int		check_value;
	int		*pipe_fd;
	t_node	*tmp;

	tmp = node;
	check_value = check_pipe(node);
	if (check_value & PIPE_NEXT)
	{
		while (tmp->type != T_PIPE)
			tmp = tmp->next;
		pipe_fd = tmp->pipe;
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	tmp = node;
	if (check_value & PIPE_PREVIOUS)
	{
		while (tmp->type != T_PIPE)
			tmp = tmp->previous;
		pipe_fd = tmp->pipe;
		close(pipe_fd[1]);
		if(!stdin_occupied(node))
			dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
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
