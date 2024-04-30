/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lferro <lferro@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 21:20:56 by lferro            #+#    #+#             */
/*   Updated: 2024/04/30 21:21:51 by lferro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	add_to_history(char *line)
{
	add_history(line);
	remove_end_newline(line);
}
