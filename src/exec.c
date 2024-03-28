#include "minishell.h"

void exec(char **cmd, t_stack **stack)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		execve(cmd[0], cmd, NULL);//, env);
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
		builtin_export(env, cmd[1]);
	else
		return 0;
	return 1;
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
	while(node)
	{
		if(!node) 
			break;
		if(node->type == T_CMD)
		{
			if (is_builtin(node->cmd, hist, env))
				;
			else
			{
				node->cmd[0] = get_cmd_path(node->cmd[0], path);
				if(node->cmd)
					exec(node->cmd, &pid_stack);
			}
		}
		node = node->next;
	}

	while(pid_stack)
	{
		wait4(pid_stack->value, &status, 0, &usage); // this should not be here. To work proprely, we need to launch all the process in prompt and then wait for all process to finish
		stack_drop(&pid_stack);	
	}
	return 0;
}
