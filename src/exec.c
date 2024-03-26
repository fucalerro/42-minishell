#include "minishell.h"
void exec(char **cmd)
{
	pid_t	pid;
	pid = fork();
	if (pid == 0)
		execve(cmd[0], cmd, NULL);//, env);
	else
		wait(NULL);
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
int is_builtin(char **cmd)
{
	if (!ft_strcmp(cmd[0],"cd"))
		builtin_cd(cmd[1]);
	else if (!ft_strcmp(cmd[0],"exit"))
		builtin_exit();
	else
		return 0;
	return 1;
}
int exe_prompt(t_node *node, char **env)
{
	char **path;

	path = get_path(env);
	if(node && node->cmd)
	{
		if (is_builtin(node->cmd))
			;
		else
		{
			node->cmd[0] = get_cmd_path(node->cmd[0], path);
			if(node->cmd)
				exec(node->cmd);
		}
	}
	return 0;
}
// there we can see how to fetch the path and after that we see how create the cmd
//	input.path = get_path(envp);
//	input.cmd = get_cmd(argv[input.i_cmd + 2], input.path);
