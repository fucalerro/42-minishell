#include "history.h"
#include "minishell.h"

void	remove_end_newline(char *line)
{
	int i;

	i = 0;
	while (line[i])
		i++;
	if (line[i - 1] == '\n')
		line[i - 1] = 0;
}

char	*get_history_path(void)
{
	char *home;
	char *path;
	char *filename = ".minishell_history";

	home = getenv("HOME");
	path = ft_strjoin(home, filename);

	return (filename);

	// return (path);
}

void	ft_read_history(t_hist **hist)
{
	int	hist_fd;
	char *home;
	char *line;
	char *path;

	path = get_history_path();

	hist_fd = open(path, O_RDONLY, 0644);
	if (hist_fd < 0)
	{
		hist_fd = open(path, O_CREAT, 0644);
		if (hist_fd < 0)
		{
			// free(path);
			return ;
		}
		// free(path);
		return ;
	}
	// free(path);

	line  = "";
	if (hist_fd >= 0)
	{
		line = get_next_line(hist_fd);
		while (line)
		{
			if (line)
			{
				remove_end_newline(line);
				add_to_history(hist, line);
				free(line);
			}
			line = get_next_line(hist_fd);
		}
	}

}

int	ft_write_history_file(char *line)
{
	int	hist_fd;
	char *path;

	remove_end_newline(line);

	path = get_history_path();

	hist_fd = open(path, O_RDWR | O_APPEND | O_CREAT, 0644);

	PL;
	ft_putstr_fd(line, hist_fd);
	ft_putstr_fd("\n", hist_fd);

	// free(path);
	return (0);
}



// t_hist	*hist_new(char *line)
// {
// 	t_hist	*node;

// 	node = (t_hist *)malloc(sizeof(struct s_hist));
// 	if (!node)
// 		return ((t_hist *)0);
// 	node->line = line;
// 	node->previous = (t_hist *)0;
// 	node->next = (t_hist *)0;
// 	return (node);
// }

// t_hist	*hist_last(t_hist *hist)
// {
// 	if (!hist)
// 		return ((t_hist *)0);
// 	while (hist->next)
// 		hist = hist->next;
// 	return (hist);
// }

void	add_to_history(t_hist **hist, char *line)
{
	t_hist	*history;
	t_hist	*new;

	add_history(line);
	remove_end_newline(line);
	// ft_write_history_file(line);

	// new = hist_new(line);
	// if (*hist)
	// {
	// 	history = hist_last(*hist);
	// 	history->next = new;
	// 	new->previous = history;
	// }
	// else
	// 	*hist = new;
}

void	print_hist()
{
	int hist_fd;
	char *path;

	path = get_history_path();

	hist_fd = open(path, O_RDONLY);
	char *line;
	line = get_next_line(hist_fd);
	while (line)
	{
		if (line)
			printf("%s", line);
		line = get_next_line(hist_fd);
	}
}



// void	print_hist(t_hist *hist)
// {
// 	int hist_fd;
// 	char *home;
// 	char *path;

// 	path = ft_strjoin(getenv("HOME"), "/.minishell_history");
// 	hist_fd = open(path, O_RDONLY);
// 	char *line;
// 	line = "";
// 	if (hist_fd >= 0)
// 	{
// 		while (line)
// 		{
// 			line = get_next_line(hist_fd);
// 			if (line)
// 				printf("%s", line);
// 		}
// 	}

// }

// void    clear_hist(t_hist **hist)
// {
//     t_hist  *tmp;

//     while (*hist)
//     {
//         tmp = *hist;
//         *hist = tmp->next;
//         free(tmp->line);
//         free(tmp);
//     }
//     *hist = NULL;
// }
