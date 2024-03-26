#include "minishell.h"

extern char **environ;

#ifndef UNIT_TESTS

int main(int ac, char **av, char **env)
{
    char *line = "-> ";
    char *prompt;
    char **tokens;

    while((prompt = readline(line)))
    {
        tokens = tokenizer(prompt);
        parser(tokens);
    }

    return (0);
}
#endif


// (cd /tmp && touch "file" && "echo'hello'" > file && grep 'hello' file | tee result.txt) || echo 'Error' > error.log
