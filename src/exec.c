#include "minishell.h"

char	*get_cmd_path(char *raw, char **path)
{
    char	*cmd;
    char	*tmp;

    cmd = raw;
	if(!*path)
		return NULL;
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
    //free_cmd(cmd);
    return (NULL);
}

int check_pipe(t_node *node)
{
	int return_value;
	t_node *tmp;

	tmp = node;
	return_value = 0;
	while(tmp && tmp->type != T_PIPE)
		tmp = tmp->next;
	if(tmp && tmp->type == T_PIPE && tmp->active)
		return_value += 1;
	tmp=node;
	while(tmp && tmp->type != T_PIPE)
		tmp = tmp->previous;
	if(tmp && tmp->type == T_PIPE && tmp->active)
		return_value += 2;
	return(return_value);
}
int run_redirection_file(t_node *node)
{
	t_node *node_tmp;
	node_tmp = node;
	int return_value;

	return_value = 0;

	while(node_tmp && node_tmp->previous && node_tmp->previous->type != T_PIPE)
		node_tmp = node_tmp->previous;
	while (node_tmp && node_tmp->type != T_PIPE)
	{
		if (node_tmp->type == T_CMD && node_tmp != node)
			return 0;
		else if (node_tmp->type == T_INFILE)
			return_value = exe_infile(node_tmp);
		else if (node_tmp->type == T_HEREDOC)
			return_value = exe_heredoc(node_tmp);
		else if (node_tmp->type == T_OUTFILE)
			return_value = exe_outfile(node_tmp);
		else if (node_tmp->type == T_OUTFILE_APPEND)
			return_value = exe_outfile_append(node_tmp);
		if(return_value)
			return return_value;
		node_tmp = node_tmp->next;
	}
	return return_value;
}
int set_pipe(t_node *node)
{
	int check_value;
	int  *pipe_fd;

	check_value = check_pipe(node);
	if (check_value & PIPE_NEXT)
	{
		pipe_fd = node->next->pipe;
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	if (check_value & PIPE_PREVIOUS)
	{
		pipe_fd = node->previous->pipe;
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
	}
	return 0;
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
		return NULL;
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


int is_builtin(char **cmd)
{
	if (!ft_strcmp(cmd[0],"cd"))
		return 1;
	else if (!ft_strcmp(cmd[0], "history"))
		return 1;
	else if (!ft_strcmp(cmd[0],"exit"))
		return 1;
	else if (!ft_strcmp(cmd[0],"env"))
		return 1;
	else if (!ft_strcmp(cmd[0],"export"))
		return 1;
	else if (!ft_strcmp(cmd[0], "pwd"))
		return 1;
	else if (!ft_strcmp(cmd[0], "unset"))
		return 1;
	//else if (!ft_strcmp(cmd[0], "echo"))
	//	return 1;
	else
		return 0;
}

int exe_builtin(t_node *node, t_hist **hist, char ***env)
{
	char **cmd = node->cmd;
	if (!ft_strcmp(cmd[0],"cd"))
		return builtin_cd(cmd[1], *env);
	else if (!ft_strcmp(cmd[0], "history"))
		builtin_history(cmd, hist, *env);
	else if (!ft_strcmp(cmd[0],"exit"))
		return builtin_exit(node);
	else if (!ft_strcmp(cmd[0],"env"))
		builtin_env(*env);
	else if (!ft_strcmp(cmd[0],"export"))
		return (builtin_export(env, cmd));
	else if (!ft_strcmp(cmd[0],"pwd"))
		printf("%s\n",builtin_pwd());
	else if (!ft_strcmp(cmd[0], "unset"))
		builtin_unset(env, cmd);
	else if (!ft_strcmp(cmd[0], "echo"))
		builtin_echo(node);
	return 0;
}
int cmd_do_not_include_path(char *cmd)
{
	while(*cmd)
	{
		if (*cmd == '/')
			return 0;
		cmd++;
	}
	return (1);
}

int init_pipe(t_node *node)
{
	while (node)
	{
		if (node->type == T_PIPE && node->active)
			pipe(node->pipe);
		node = node->next;
	}
	return 0;
}
int close_pipe(t_node *node)
{
	while (node)
	{
		if (node->type == T_PIPE && node->active)
		{
			close(node->pipe[0]);
			close(node->pipe[1]);
		}
		node = node->next;
	}
	return 0;
}


int run_cmd(char **path, t_node *node, t_hist **hist, t_stack **pid_stack, char ***env)
{
	pid_t	pid;
	char **cmd;

	cmd = node->cmd;
	if (is_builtin(cmd))
	{
		set_pipe(node);
		run_redirection_file(node);
		return exe_builtin(node, hist, env);
	}
	else if (!path)
	{
		write_err("minishell: command not found: ");
		write_err(cmd[0]);
		write_err("\n");
		return(ERR_CMD_NOT_FOUND);
	}
	else
	if (cmd_do_not_include_path(node->cmd[0]))
	{
		node->cmd[0] = get_cmd_path(node->cmd[0], path);
	}
	else
	{
		struct stat path_stat;
		stat(node->cmd[0], &path_stat);

		// Check if it's a directory
		if (access(node->cmd[0], F_OK))
		{
			perror(NULL);
			return(ERR_CMD_NOT_FOUND);
		}
		if (S_ISDIR(path_stat.st_mode)) 
		{
			perror(NULL);
			return(ERR_CMD_CANT_EXE);
		}
		if (access(node->cmd[0], X_OK))
		{
			perror(NULL);
			return(ERR_CMD_CANT_EXE);
		}
	}

	if (!node->cmd[0])
	{
		write_err(" command not found\n");
		return(ERR_CMD_NOT_FOUND);
	}

	pid = fork();
	if (pid == 0)
	{
		set_pipe(node);
		if(run_redirection_file(node))
			exit(EXIT_FAILURE);
		execve(cmd[0], cmd, NULL);
		exit(EXIT_FAILURE);
	}
	else
	{
		stack_add(pid_stack, pid);
		if (check_pipe(node) & PIPE_PREVIOUS)
		{
			close(node->previous->pipe[0]);
			close(node->previous->pipe[1]);
		}
	}
	return 0;
}

int exe_prompt(t_node *list, char ***env, t_hist **hist, int *status)
{

    struct rusage usage; // For resource usage info
    char **path;
    t_node *node;
    t_stack *pid_stack;

	pid_stack = NULL;
	node = list;

	path = get_path(*env);
	//while loop to exec
	init_pipe(node);
	while(node)
	{
		if(!node) 
			break;
		if (node->type == T_CMD)
		{
			*status = run_cmd(path, node, hist, &pid_stack, env);
		}
		node = node->next;
	}

	close_pipe(list);
	// PL;
	if (path)
		free_string_array(path);

	//while loop to waitpid
	while(pid_stack)
	{
		wait4(pid_stack->value, status, 0, &usage);
		if (WIFEXITED(*status))
			*status = WEXITSTATUS(*status);
		stack_drop(&pid_stack);	
	}
	return 0;
}
