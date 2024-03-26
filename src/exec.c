#include "minishell.h"
/*
void exec()
{
	char *args[] = {"/usr/bin/touch", "okokokokok", NULL};  // Arguments array
	pid_t	pid;
	pid = fork();
	if (pid == 0)
		execve(args[0], args, env);
	else
		wait(NULL);
}


char	**get_cmd(char *raw, char **path)
{
	char	**cmd;
	char	*tmp;

	cmd = ft_split(raw, ' ');
	while (*path)
	{
		tmp = ft_strjoin(*path, cmd[0]);
		if (!access(tmp, X_OK))
		{
			free(cmd[0]);
			cmd[0] = tmp;
			return (cmd);
		}
		free(tmp);
		path++;
	}
	free_cmd(cmd);
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

// there we can see how to fetch the path and after that we see how create the cmd
	input.path = get_path(envp);
	input.cmd = get_cmd(argv[input.i_cmd + 2], input.path);


*/
