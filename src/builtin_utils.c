#include "minishell.h"

int	is_builtin(char **cmd)
{
	if (!ft_strcmp(cmd[0], "cd"))
		return (1);
	else if (!ft_strcmp(cmd[0], "history"))
		return (1);
	else if (!ft_strcmp(cmd[0], "exit"))
		return (1);
	else if (!ft_strcmp(cmd[0], "env"))
		return (1);
	else if (!ft_strcmp(cmd[0], "export"))
		return (1);
	else if (!ft_strcmp(cmd[0], "pwd"))
		return (1);
	else if (!ft_strcmp(cmd[0], "unset"))
		return (1);
	else if (!ft_strcmp(cmd[0], "echo"))
		return (1);
	else
		return (0);
}
int	exe_builtin(t_node *node, char ***env)
{
	char	**cmd;

	cmd = node->cmd;
	if (!ft_strcmp(cmd[0], "cd"))
		return (builtin_cd(cmd[1], *env));
	else if (!ft_strcmp(cmd[0], "history"))
		builtin_history(cmd);
	else if (!ft_strcmp(cmd[0], "exit"))
		return (builtin_exit(node));
	else if (!ft_strcmp(cmd[0], "env"))
		builtin_env(*env);
	else if (!ft_strcmp(cmd[0], "export"))
		return (builtin_export(env, cmd));
	else if (!ft_strcmp(cmd[0], "pwd"))
		printf("%s\n", builtin_pwd());
	else if (!ft_strcmp(cmd[0], "unset"))
		builtin_unset(env, cmd);
	else if (!ft_strcmp(cmd[0], "echo"))
		builtin_echo(node);
	return (0);
}
int	run_builtin(t_node *node, t_stack **pid_stack, char ***env)
{
	pid_t	pid;

	if (node->active == 2)
	{
		pid = fork();
		signal(SIGINT, sigint_handler_process); // Ctrl-C
		if (pid)
		{
			stack_add(pid_stack, pid);
			return (0);
		}
		else
		{
			set_pipe(node);
			close_pipe(node);
			if (!run_redirection_file(node))
				exit(exe_builtin(node, env));
			else
				exit(1);
		}
	}
	if (!run_redirection_file(node))
		return (exe_builtin(node, env));
	else
		return (1);
}
void	flag_builtin_fork(t_node *node)
{
	t_node	*tmp;

	tmp = node;
	while (tmp && tmp->type != T_PIPE)
		tmp = tmp->next;
	if (!tmp || tmp->type != T_PIPE)
		return ;
	tmp = node;
	while (tmp)
	{
		if (tmp->type == T_CMD)
			tmp->active = 2;
		tmp = tmp->next;
	}
}
