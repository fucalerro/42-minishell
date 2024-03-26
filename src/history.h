#ifndef HISTORY_H
# define HISTORY_H

typedef struct s_hist
{
    char            *line;
    struct s_hist   *previous;
    struct s_hist   *next;
}                   t_hist;

void    hist_append(t_hist **hist, char *line);
void    print_hist(t_hist *hist);

#endif
