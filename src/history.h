#ifndef HISTORY_H
# define HISTORY_H

typedef struct s_hist
{
    char            *line;
    struct s_hist   *previous;
    struct s_hist   *next;
}                   t_hist;

void    add_to_history(t_hist **hist, char *line);
void    print_hist(void);
char	*get_history_path(void);
void	ft_read_history(t_hist **hist);
int     ft_write_history_file(char *line);

#endif
