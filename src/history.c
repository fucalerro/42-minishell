/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Lu-ni <lucas.nicollier@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:12:43 by Lu-ni             #+#    #+#             */
/*   Updated: 2024/04/28 22:16:00 by bob              ###   ########.fr       */
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
		{
			if (line)
			{
				remove_end_newline(line);
				add_to_history(line);
				free(line);
			}
			line = get_next_line(hist_fd);
		}
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

void	add_to_history(char *line)
{
	add_history(line);
	remove_end_newline(line);
}

void	print_hist(char **env)
{
	int		hist_fd;
	char	*path;
	char	*line;

	path = get_history_path(env);
	hist_fd = open(path, O_RDONLY);
	line = get_next_line(hist_fd);
	while (line)
	{
		if (line)
			printf("%s", line);
		line = get_next_line(hist_fd);
	}
}

void	ft_history(char *prompt, char **env)
{
	add_to_history(prompt);
	ft_write_history_file(prompt, env);
}
