/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Lu-ni <lucas.nicollier@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:12:43 by Lu-ni             #+#    #+#             */
/*   Updated: 2024/04/28 22:12:43 by Lu-ni            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd_path(t_node *node, char **path)
{
	char	*cmd;
	char	*tmp;
	int		i;

	i = -1;
	cmd = node->cmd[0];
	while (path && path[++i])
	{
		tmp = ft_strjoin(path[i], cmd);
		if (!tmp)
			break ;
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
	if (path)
		free_2starchar(path);
	return (NULL);
}

char	**get_path(char *env[])
{
	char	**tmps;
	char	*tmp;
	char	*path_env;
	int		i;

	path_env = ft_getenv("PATH", env);
	if (!path_env)
		return (NULL);
	tmps = ft_split(path_env, ':');
	if (!tmps)
		return (NULL);
	i = 0;
	while (tmps[i])
	{
		tmp = tmps[i];
		tmps[i] = ft_strjoin(tmp, "/");
		free(tmp);
		if (!tmps[i])
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

void	deal_cout(t_node *node, t_node *prev_cmd, int i, int ii)
{
	char	**tmp;

	while (prev_cmd && prev_cmd->type != T_CMD)
		prev_cmd = prev_cmd->previous;
	while ((node->cmd[i]) || prev_cmd->cmd[ii])
	{
		if (node->cmd[i])
			i++;
		if (prev_cmd->cmd[ii])
			ii++;
	}
	tmp = (char **)malloc(sizeof(char *) * (i + ii + 1));
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
}

void	deal_with_multi_cmd(t_node *node)
{
	int		cmd_seen;
	t_node	*prev_cmd;

	cmd_seen = 0;
	while (node)
	{
		if (node->type == T_CMD)
			cmd_seen++;
		if (cmd_seen > 1)
		{
			prev_cmd = node->previous;
			deal_cout(node, prev_cmd, 0, 0);
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
