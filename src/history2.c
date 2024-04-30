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