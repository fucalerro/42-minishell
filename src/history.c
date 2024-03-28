#include "history.h"
#include "minishell.h"

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
	t_hist	*list;

	list = hist;
	while (list)
	{
		printf("%s\n", list->line);
		list = list->next;
	}
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
