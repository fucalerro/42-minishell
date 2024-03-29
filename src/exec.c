#include "minishell.h"

void exec(char **cmd, t_stack **stack)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		execve(cmd[0], cmd, NULL);//, env);
		exit(EXIT_FAILURE);
	}
	else
		stack_add(stack, pid);
}


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
int is_builtin(char **cmd, t_hist **hist, char ***env)
{
	if (!ft_strcmp(cmd[0],"cd"))
		builtin_cd(cmd[1]);
	else if (!ft_strcmp(cmd[0], "history"))
		builtin_history(cmd, hist);
	else if (!ft_strcmp(cmd[0],"exit"))
		builtin_exit();
	else if (!ft_strcmp(cmd[0],"env"))
		builtin_env(*env);
	else if (!ft_strcmp(cmd[0],"export"))
		builtin_export(env, cmd);
	else if (!ft_strcmp(cmd[0], "unset"))
		builtin_unset(*env, cmd[1]);
	else
		return 0;
	return 1;
}
int run_cmd(char **path, t_node *node, t_hist **hist, t_stack **pid_stack, char ***env)
{
	pid_t	pid;
	int  (*pipe_fd)[2];
	char **cmd;

	if (node->next && node->next->type == T_PIPE)
	{
		pipe(node->next->pipe[0]);
	}
	if (is_builtin(node->cmd, hist, env))
		debug_print("this node is CMD builtin");
	else
	{
		if (node->next && node->next->type == T_PIPE) //first child/parent
		{
			debug_print("this node is CMD with next PIPE");
			node->cmd[0] = get_cmd_path(node->cmd[0], path);
			cmd = node->cmd;
			pipe_fd = node->next->pipe;
			pid = fork();
			if (pid == 0)
			{
				close(pipe_fd[0][0]);
				dup2(pipe_fd[0][1], STDOUT_FILENO);
				close(pipe_fd[0][1]);
				execve(cmd[0], cmd, NULL);
				printf("fail1\n");
			    exit(EXIT_FAILURE);
			}
			else
				stack_add(pid_stack, pid);
		}
		else if (node->previous && node->previous->type == T_PIPE) //second child/parent
		{
			debug_print("this node is CMD with previous PIPE");
			node->cmd[0] = get_cmd_path(node->cmd[0], path);
			cmd = node->cmd;
			pipe_fd = node->previous->pipe;
			pid = fork();
			if (pid == 0)
			{
				close(pipe_fd[0][1]);
				dup2(pipe_fd[0][0], STDIN_FILENO);
				close(pipe_fd[0][0]);
				execve(cmd[0], cmd, NULL);
				printf("fail2 with %s and %s\n",cmd[0], cmd[1]);
			    exit(EXIT_FAILURE);
			}
			else
				stack_add(pid_stack, pid);
		}
		else
		{
			debug_print("this node is CMD");
			node->cmd[0] = get_cmd_path(node->cmd[0], path);
			if(node->cmd)
				exec(node->cmd, pid_stack);
		}
	}
}

int exe_prompt(t_node *list, char ***env, t_hist **hist)
{

	int status;
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
		if(node->type == T_CMD)
			run_cmd(path, node, hist, &pid_stack, env);
		if (node && node->previous && node->previous->type == T_PIPE)
		{
			debug_print("closing parent side\n");
			close(node->previous->pipe[0][0]);
			close(node->previous->pipe[0][1]);
    }
		node = node->next;
	}

	//while loop to waitpid
	while(pid_stack)
	{
		wait4(pid_stack->value, &status, 0, &usage);
		stack_drop(&pid_stack);	
	}
	return 0;
}
