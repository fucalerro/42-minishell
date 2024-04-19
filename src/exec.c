#include "history.h"
#include "minishell.h"
#include "stack.h"

char	*get_cmd_path(char *raw, char **path)
{
	char	*cmd;
	char	*tmp;

	cmd = raw;
	if (!*path)
		return (NULL);
	while (*path)
	{
		tmp = ft_strjoin(*path, cmd);
		if (!access(tmp, X_OK))
		{
			free(cmd);
			cmd = tmp;
			return (cmd);
		}
		free(tmp);
		path++;
	}
	// free_cmd(cmd);
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
	int		i;

	i = 0;
	while (env[i] != NULL)
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			break ;
		i++;
	}
	if (!env[i])
		return (NULL);
	tmps = ft_split(&env[i][5], ':');
	i = 0;
	while (tmps[i])
	{
		tmp = tmps[i];
		tmps[i] = ft_strjoin(tmp, "/");
		free(tmp);
		i++;
	}
	return (tmps);
}

int	exe_builtin(t_node *node, t_hist **hist, char ***env)
{
	char	**cmd;

	cmd = node->cmd;
	if (!ft_strcmp(cmd[0], "cd"))
		return (builtin_cd(cmd[1], *env));
	else if (!ft_strcmp(cmd[0], "history"))
		builtin_history(cmd, hist, *env);
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

int run_builtin(t_node *node, t_hist **hist, t_stack **pid_stack, char ***env)
{
	pid_t		pid;
	if (node->active == 2)
	{
		pid = fork();
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
				exit(exe_builtin(node, hist, env));
			else
				exit(1);
		}
	}
	if (!run_redirection_file(node))
		return (exe_builtin(node, hist, env));
	else
		return (1);
}

int	run_cmd(char **path, t_node *node, t_hist **hist, t_stack **pid_stack,
		char ***env)
{
	pid_t		pid;
	struct stat	path_stat;

	if (is_builtin(node->cmd))
		return run_builtin(node, hist, pid_stack, env);
	else if (cmd_do_not_include_path(node->cmd[0]))
		node->cmd[0] = get_cmd_path(node->cmd[0], path);
	else
	{
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
	}
	if (!node->cmd[0])
	{
		write_err(" command not found\n");
		return (ERR_CMD_NOT_FOUND);
	}
	pid = fork();
	if (pid == 0)
	{
		set_pipe(node);
		close_pipe(node);
		if (run_redirection_file(node))
			exit(EXIT_FAILURE);
		execve(node->cmd[0], node->cmd, NULL);
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

int	exe_prompt(t_node *list, char ***env, t_hist **hist, int *status)
{
	char	**path;
	t_node	*node;
	t_stack	*pid_stack;

	struct rusage usage;
	pid_stack = NULL;
	node = list;
	path = get_path(*env);
	init_pipe(node);
	flag_builtin_fork(node);
	while (node)
	{
		if (!node)
			break ;
		if (node->type == T_CMD)
		{
			*status = run_cmd(path, node, hist, &pid_stack, env);
		}
		node = node->next;
	}
	close_pipe(list);
	if (path)
		free_string_array(path);
	while (pid_stack)
	{
		wait4(pid_stack->value, status, 0, &usage);
		if (WIFEXITED(*status))
			*status = WEXITSTATUS(*status);
		stack_drop(&pid_stack);
	}
	return (0);
}
