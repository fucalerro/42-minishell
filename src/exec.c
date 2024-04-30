/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolli <lnicolli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:12:43 by Lu-ni             #+#    #+#             */
/*   Updated: 2024/04/30 20:50:41 by lnicolli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_executable(t_node *node)
{
	struct stat	path_stat;

	if (!node->cmd || !node->cmd[0])
	{
		write_err(" command not found\n");
		return (ERR_CMD_NOT_FOUND);
	}
	stat(node->cmd[0], &path_stat);
	if (access(node->cmd[0], F_OK))
	{
		perror(NULL);
		return (ERR_CMD_NOT_FOUND);
	}
	if (S_ISDIR(path_stat.st_mode))
	{
		write_err(" is a directory\n");
		return (ERR_CMD_CANT_EXE);
	}
	if (access(node->cmd[0], X_OK))
	{
		perror(NULL);
		return (ERR_CMD_CANT_EXE);
	}
	return (0);
}

int	run_cmd(t_node *node, t_stack **pid_stack, char ***env)
{
	pid_t	pid;

	if (is_builtin(node->cmd))
		return (run_builtin(node, pid_stack, env));
	else if (cmd_do_not_include_path(node->cmd[0]))
		get_cmd_path(node, get_path(*env));
	node->active = check_executable(node);
	pid = fork();
	set_signal(1);
	if (pid == 0)
	{
		set_pipe(node);
		close_pipe(node);
		if (run_redirection_file(node))
			exit(EXIT_FAILURE);
		if (node->active)
			exit(node->active);
		execve(node->cmd[0], node->cmd, *env);
		exit(EXIT_FAILURE);
	}
	else
		stack_add(pid_stack, pid);
	if (node->active)
		return (node->active);
	return (0);
}

void	wait_pid(t_stack *pid_stack, int *status)
{
	struct rusage	usage;

	while (pid_stack)
	{
		wait4(pid_stack->value, status, 0, &usage);
		if (WIFEXITED(*status))
			*status = WEXITSTATUS(*status);
		stack_drop(&pid_stack);
	}
}
int	max_pipe(t_node *node)

int	max_pipe(t_node *node)
{
	int	pipe_number;

	pipe_number = 0;
	while (node)
	{
		if (node->type == T_PIPE)
			pipe_number++;
		node = node->next;
	}
	if (pipe_number > (100))
	{
		write_err("too much pipe\n");
		return (1);
	}
	return (0);
}

int	exe_prompt(t_node *list, char ***env, int *status)
{
	t_node	*node;
	t_stack	*pid_stack;

	deal_with_multi_cmd(list);
	pid_stack = NULL;
	node = list;
	if (max_pipe(list))
	{
		free_lst(node);
		return (1);
	}
	init_pipe(node);
	flag_builtin_fork(node);
	while (node)
	{
		if (node->type == T_CMD)
			*status = run_cmd(node, &pid_stack, env);
		node = node->next;
	}
	close_pipe(list);
	wait_pid(pid_stack, status);
	free_lst(list);
	return (0);
}
