#include "minishell.h"

extern char **environ;

#ifndef UNIT_TESTS

int main(int ac, char **av, char **env)
{
    char *line = builtin_pwd();
    char *prompt;
    char **tokens;

    t_node *lst;
    t_hist *history;
    char **env_copy;

    history = NULL;

    line = ft_strjoin(line, "🌻 ");

    env_copy = copy_env(env);

    while((prompt = readline(line)))
    {
        if (strcmp(prompt, ""))
        {
            hist_append(&history, prompt);
            add_history(prompt);
        }
        tokens = tokenizer(prompt);
        lst = parser(tokens);
        exe_prompt(lst, &env_copy, &history);
        line = builtin_pwd();
        line = ft_strjoin(line, "🌻 ");
    }

    return (0);
}
#endif
