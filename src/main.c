#include "minishell.h"

extern char **environ;

#ifndef UNIT_TESTS

int main(int ac, char **av, char **env)
{
    char *line = builtin_pwd();
    char *prompt;
    char **tokens;

    t_node *lst;

    t_hist *hist;
    
    hist = NULL;

    t_hist *hist;
    
    hist = NULL;

	line = ft_strjoin(line, "🌻 ");
    while((prompt = readline(line)))
    {
        hist_append(&hist, prompt);

        add_history(prompt);

        tokens = tokenizer(prompt);
        lst = parser(tokens);
		
     //   print_list(lst);

		exe_prompt(lst, env);
		line = builtin_pwd();
		line = ft_strjoin(line, "🌻 ");
    }

    return (0);
}
#endif
