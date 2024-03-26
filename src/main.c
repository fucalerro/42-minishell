#include "minishell.h"

extern char **environ;

#ifndef UNIT_TESTS

int main(int ac, char **av, char **env)
{
    char *line = "-> ";
    char *prompt;
    char **tokens;

    t_node *lst;

    t_hist *hist;
    
    hist = NULL;

    while((prompt = readline(line)))
    {
        hist_append(&hist, prompt);

        add_history(prompt);

        tokens = tokenizer(prompt);
        lst = parser(tokens);

        print_list(lst);
    }

    return (0);
}
#endif
