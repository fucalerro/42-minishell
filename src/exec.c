#include "minishell.h"

char	*get_cmd_path(char *raw, char **path)
{
    char	*cmd;
    char	*tmp;

    cmd = raw;
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

	return_value = 0;
	if(node && node->next && node->next->type == T_PIPE)
		return_value += 1;
	if(node && node->previous && node->previous->type == T_PIPE)
		return_value += 2;
	return(return_value);
}
int set_pipe(t_node *node)
{
	int check_value;
	int  (*pipe_fd)[2];
	t_node *node_tmp;

	check_value = check_pipe(node);
	if (check_value & PIPE_NEXT)
	{
		pipe_fd = node->next->pipe;
		close(pipe_fd[0][0]);
		dup2(pipe_fd[0][1], STDOUT_FILENO);
		close(pipe_fd[0][1]);
	}
	if (check_value & PIPE_PREVIOUS)
	{
		pipe_fd = node->previous->pipe;
		close(pipe_fd[0][1]);
		dup2(pipe_fd[0][0], STDIN_FILENO);
		close(pipe_fd[0][0]);
	}
	node_tmp = node;
	while(node_tmp && node_tmp->previous && node_tmp->previous->type != T_PIPE)
		node_tmp = node_tmp->previous;
	while (node_tmp && node_tmp->type != T_PIPE)
	{
		if (node_tmp->type == T_CMD && node_tmp != node)
			return 0;
		if (node_tmp->type == T_INFILE)
			exe_infile(node_tmp);
		if (node_tmp->type == T_HEREDOC)
			exe_heredoc(node_tmp);
		if (node_tmp->type == T_OUTFILE)
			exe_outfile(node_tmp);
		if (node_tmp->type == T_OUTFILE_APPEND)
			exe_outfile_append(node_tmp);
		node_tmp = node_tmp->next;
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
	else
		return 0;
}

int exe_builtin(char **cmd, t_hist **hist, char ***env)
{
	if (!ft_strcmp(cmd[0],"cd"))
		builtin_cd(cmd[1]);
	else if (!ft_strcmp(cmd[0], "history"))
		builtin_history(cmd, hist);
	else if (!ft_strcmp(cmd[0],"exit"))
		builtin_exit(cmd[1]);
	else if (!ft_strcmp(cmd[0],"env"))
		builtin_env(*env);
	else if (!ft_strcmp(cmd[0],"export"))
		builtin_export(env, cmd);
	else if (!ft_strcmp(cmd[0],"pwd"))
		printf("%s\n",builtin_pwd());
	else if (!ft_strcmp(cmd[0], "unset"))
		builtin_unset(env, cmd);
	else
		return 0;
	return 1;
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
int run_cmd(char **path, t_node *node, t_hist **hist, t_stack **pid_stack, char ***env)
{
	pid_t	pid;
	char **cmd;

	cmd = node->cmd;
	if (is_builtin(cmd))
	{
		set_pipe(node);
		exe_builtin(cmd, hist, env);
		return 0;
	}

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
		execve(cmd[0], cmd, NULL);
		exit(EXIT_FAILURE);
	}
	else
	{
		stack_add(pid_stack, pid);
		if (check_pipe(node) & PIPE_PREVIOUS)
		{
			close(node->previous->pipe[0][0]);
			close(node->previous->pipe[0][1]);
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
	while(node)
	{
		if(!node) 
			break;
		if (node->next && node->next->type == T_PIPE)
			pipe(node->next->pipe[0]);
		if (node->type == T_CMD)
			*status = run_cmd(path, node, hist, &pid_stack, env);
		node = node->next;
	}

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
