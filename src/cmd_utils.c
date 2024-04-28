#include "minishell.h"

char	*get_cmd_path(t_node *node, char **path)
{
	char	*cmd;
	char	*tmp;
	int i;

	i = -1;
	cmd = node->cmd[0];
	while (path && path[++i])
	{
		tmp = ft_strjoin(path[i], cmd);
		if(!tmp)
			break;
		if (!access(tmp, X_OK))
		{
			free(cmd);
			free_2starchar(path);
			node->cmd[0] = tmp;
			return (tmp);
		}
		free(tmp);
	}
	node->cmd = free_2starchar(node->cmd);
	if(path)
		free_2starchar(path);
	return (NULL);
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
