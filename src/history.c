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

void	ft_read_history(t_hist **hist)
{
	int	hist_fd;
	char *home;
	char *line;
	char *path;


	home = getenv("HOME");
	path = ft_strjoin(home, "/.minishell_history");
	hist_fd = open(path, O_RDWR | O_CREAT, 0644);


	line  = "";
	if (hist_fd >= 0)
	{
		while (line)
		{
			line = get_next_line(hist_fd);
			if (line)
			{
				hist_append(hist, line);
				remove_end_newline(line);
				add_history(line);
			}
		}
	}
}

int	ft_write_history_file(char *line)
{
	int	hist_fd;
	char *home;
	char *path;

	home = getenv("HOME");
	path = ft_strjoin(home, "/.minishell_history");
	hist_fd = open(path, O_RDWR | O_APPEND | O_CREAT, 0644);
	
	ft_putstr_fd(line, hist_fd);
	ft_putstr_fd("\n", hist_fd);


	return (0);
}



t_hist	*hist_new(char *line)
{
	t_hist	*node;

	node = (t_hist *)malloc(sizeof(struct s_hist));
	if (!node)
		return ((t_hist *)0);
	node->line = line;
	node->previous = (t_hist *)0;
	node->next = (t_hist *)0;
	return (node);
}

t_hist	*hist_last(t_hist *hist)
{
	if (!hist)
		return ((t_hist *)0);
	while (hist->next)
		hist = hist->next;
	return (hist);
}

void	hist_append(t_hist **hist, char *line)
{
	t_hist	*history;
	t_hist	*new;

	new = hist_new(line);
	if (*hist)
	{
		history = hist_last(*hist);
		history->next = new;
		new->previous = history;
	}
	else
		*hist = new;
}

void	print_hist(t_hist *hist)
{
	int hist_fd;
	char *home;
	char *path;

	path = ft_strjoin(getenv("HOME"), "/.minishell_history");
	hist_fd = open(path, O_RDONLY);
	char *line;
	line = "";
	if (hist_fd >= 0)
	{
		while (line)
		{
			line = get_next_line(hist_fd);
			if (line)
				printf("%s", line);
		}
	}

	// t_hist	*list;

	// list = hist;
	// while (list)
	// {
	// 	printf("%s\n", list->line);
	// 	list = list->next;
	// }
}

void    clear_hist(t_hist **hist)
{
    t_hist  *tmp;

    while (*hist)
    {
        tmp = *hist;
        *hist = tmp->next;
        free(tmp->line);
        free(tmp);
    }
    *hist = NULL;
}
