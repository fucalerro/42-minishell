/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Lu-ni <lucas.nicollier@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:12:42 by Lu-ni             #+#    #+#             */
/*   Updated: 2024/04/28 22:12:42 by Lu-ni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*builtin_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		return (cwd);
	}
	else
	{
		perror("getcwd() error");
	}
	return (NULL);
}

int	builtin_cd(const char *path, char **env)
{
	if (path == NULL)
	{
		path = ft_getenv("HOME", env);
		if (path == NULL)
		{
			write_err("cd: HOME not set\n");
			return (1);
		}
	}
	if (chdir(path) != 0)
	{
		perror(" cd");
		return (1);
	}
	return (0);
}

void	builtin_history(char **cmd, char **env)
{
	char	*path;

	if (!cmd[1])
	{
		print_hist(env);
	}
	else if (!ft_strcmp(cmd[1], "-c"))
	{
		path = get_history_path(env);
		unlink(path);
		rl_clear_history();
	}
}

int	builtin_exit(t_node *node)
{
	char	*cmd;

	if (!node->cmd[1])
		exit(0);
	if (node->cmd[1] && node->cmd[2])
	{
		write_err(" too many arguments\n");
		return (1);
	}
	cmd = node->cmd[1];
	if (*cmd == '-' || *cmd == '+')
		cmd++;
	while (*cmd)
	{
		if (!ft_isdigit(*cmd))
		{
			write_err(" numeric argument required\n");
			exit(255);
		}
		cmd++;
	}
	if (node->cmd[1])
		exit(atoi(node->cmd[1]));
	return (0);
}

int	builtin_echo(t_node *node)
{
	char	**cmd;
	int		i;
	int		new_line;

	cmd = node->cmd;
	i = 1;
	new_line = 1;
	if (!cmd[1])
	{
		ft_putstr_fd("\n", 1);
		return (1);
	}
	if (cmd[1][0] == '-' && cmd[1][1] == 'n' && !cmd[1][2])
	{
		i++;
		new_line = 0;
	}
	if (cmd[i])
		ft_putstr_fd(cmd[i++], 1);
	while (cmd[i])
		ft_putstr_fd(ft_strjoin(" ", cmd[i++]), 1);
	if (new_line)
		ft_putstr_fd("\n", 1);
	return (0);
}
