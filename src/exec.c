#include "minishell.h"
#include "node.h"

char	*get_cmd_path(t_node *node, char **path)
{
	char	*cmd;
	char	*tmp;
	int i;

	i = -1;
	cmd = node->cmd[0];
	if (!path || !*path)
	{
		free_2starchar(node->cmd);
		return (NULL);
	}
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], cmd);
		if(!tmp)
		{
			free_2starchar(node->cmd);
			node->cmd = NULL;
			free_2starchar(path);
			return (NULL);
		}
		if (!access(tmp, X_OK))
		{
			free(cmd);
			free_2starchar(path);
			node->cmd[0] = tmp;
			return (tmp);
		}
		free(tmp);
	}
	free_2starchar(node->cmd);
	node->cmd = NULL;
	free_2starchar(path);
	return (NULL);
}

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

int	run_redirection_file(t_node *node)
{
	t_node	*node_tmp;
	int		return_value;

	node_tmp = node;
	return_value = 0;
	while (node_tmp && node_tmp->previous && node_tmp->previous->type != T_PIPE)
		node_tmp = node_tmp->previous;
	while (node_tmp && node_tmp->type != T_PIPE)
	{
		if (node_tmp->type == T_CMD && node_tmp != node)
			return (0);
		else if (node_tmp->type == T_INFILE)
			return_value = exe_infile(node_tmp);
		else if (node_tmp->type == T_HEREDOC)
			return_value = exe_heredoc(node_tmp);
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

char	**get_path(char *env[])
{
	char	**tmps;
	char	*tmp;
	char *path_env;
	int		i;

	path_env = ft_getenv("PATH", env);
	if(!path_env)
		return NULL;
	tmps = ft_split(path_env, ':');
	if(!tmps)
		return NULL;
	i = 0;
	while (tmps[i])
	{
		tmp = tmps[i];
		tmps[i] = ft_strjoin(tmp, "/");
		free(tmp);
		if(!tmps[i])
			return (NULL);
		i++;
	}
	return (tmps);
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

int	cmd_do_not_include_path(char *cmd)
{
	while (*cmd)
	{
		if (*cmd == '/')
			return (0);
		cmd++;
	}
	return (1);
}

int run_builtin(t_node *node, t_stack **pid_stack, char ***env)
{
	pid_t		pid;
	if (node->active == 2)
	{
		pid = fork();
		signal(SIGINT, sigint_handler_process);   // Ctrl-C
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
	if (executable_ok)
		return (executable_ok);
	pid = fork();
	signal(SIGINT, sigint_handler_process);   // Ctrl-C
	if (pid == 0)
	{
		set_pipe(node);
		close_pipe(node);
		if (run_redirection_file(node))
			exit(EXIT_FAILURE);
		execve(node->cmd[0], node->cmd, *env);
		exit(EXIT_FAILURE);
	}
	else
		stack_add(pid_stack, pid);
	return (0);
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
