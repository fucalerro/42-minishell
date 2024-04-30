/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicolli <lnicolli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:12:43 by Lu-ni             #+#    #+#             */
/*   Updated: 2024/04/30 20:35:51 by lnicolli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"
#include "minishell.h"

void	remove_end_newline(char *line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	if (i > 0 && line[i - 1] == '\n')
		line[i - 1] = 0;
}

char	*get_history_path(char **env)
{
	char	*home;
	char	*filename;
	char	*path;

	filename = "/.minishell_history";
	home = ft_getenv("HOME", env);
	if (!home)
		return (0);
	path = ft_strjoin(home, filename);
	return (path);
}

void	ft_read_history_loop(char **line, int hist_fd)
{
	while (*line)
	{
		if (*line)
		{
			remove_end_newline(*line);
			add_to_history(*line);
			free(*line);
		}
		*line = get_next_line(hist_fd);
	}
}

void	ft_read_history(char **env)
{
	int		hist_fd;
	char	*line;
	char	*path;

	path = get_history_path(env);
	hist_fd = open(path, O_RDONLY, 0644);
	if (hist_fd < 0)
	{
		hist_fd = open(path, O_CREAT, 0644);
		if (hist_fd < 0)
		{
			free(path);
			return ;
		}
	}
	free(path);
	line = "";
	if (hist_fd >= 0)
	{
		line = get_next_line(hist_fd);
		while (line)
			ft_read_history_loop(&line, hist_fd);
		close(hist_fd);
	}
	free(line);
}

int	ft_write_history_file(char *line, char **env)
{
	int		hist_fd;
	char	*path;

	remove_end_newline(line);
	path = get_history_path(env);
	hist_fd = open(path, O_RDWR | O_APPEND | O_CREAT, 0644);
	ft_putstr_fd(line, hist_fd);
	ft_putstr_fd("\n", hist_fd);
	free(path);
	close(hist_fd);
	return (0);
}
