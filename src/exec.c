#include "minishell.h"
#include "node.h"


int check_executable(t_node *node)
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
	pid_t		pid;
	int 		executable_ok;

	if (is_builtin(node->cmd))
		return run_builtin(node, pid_stack, env);
	else if (cmd_do_not_include_path(node->cmd[0]))
		get_cmd_path(node, get_path(*env));
	executable_ok = check_executable(node);
	pid = fork();
	signal(SIGINT, sigint_handler_process);   // Ctrl-C
	if (pid == 0)
	{
		set_pipe(node);
		close_pipe(node);
		if (run_redirection_file(node))
			exit(EXIT_FAILURE);
		if (executable_ok)
			exit(executable_ok);
		execve(node->cmd[0], node->cmd, *env);
		exit(EXIT_FAILURE);
	}
	else
		stack_add(pid_stack, pid);
		if (executable_ok)
			return (executable_ok);
	return (0);
}
void wait_pid(t_stack *pid_stack, int *status)
{
	struct rusage usage;

	while (pid_stack)
	{
		wait4(pid_stack->value, status, 0, &usage);
		if (WIFEXITED(*status))
			*status = WEXITSTATUS(*status);
		stack_drop(&pid_stack);
	}
}
void	deal_with_multi_cmd(t_node *node)
{
	int		cmd_seen;
	t_node	*prev_cmd;
	char	**tmp;
	int		count;
	int		i;
	int		ii;

	cmd_seen = 0;
	prev_cmd = NULL;
	while (node)
	{
		if (node->type == T_CMD)
			cmd_seen++;
		if (cmd_seen > 1)
		{
			prev_cmd = node->previous;
			while (prev_cmd && prev_cmd->type != T_CMD)
				prev_cmd = prev_cmd->previous;
			count = 0;
			i = 0;
			while (node->cmd[i++])
				count++;
			i = 0;
			while (prev_cmd->cmd[i++])
				count++;
			tmp = (char **)malloc(sizeof(char *) * (count + 1));
			if (!tmp)
				return ;
			ii = 0;
			i = 0;
			while (prev_cmd->cmd[i])
				tmp[ii++] = prev_cmd->cmd[i++];
			i = 0;
			while (node->cmd[i])
				tmp[ii++] = node->cmd[i++];
			tmp[ii] = NULL;
			free(prev_cmd->cmd);
			prev_cmd->cmd = tmp;
			node->previous->next = node->next;
			if (node->next)
				node->next->previous = node->previous;
			prev_cmd = node->previous;
			free(node->cmd);
			free(node);
			node = prev_cmd;
			cmd_seen = 1;
		}
		if (node->type == T_PIPE)
			cmd_seen = 0;
		node = node->next;
	}
}
int	exe_prompt(t_node *list, char ***env, int *status)
{
	t_node	*node;
	t_stack	*pid_stack;

	deal_with_multi_cmd(list);
	pid_stack = NULL;
	node = list;
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
