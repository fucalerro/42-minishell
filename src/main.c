#include "minishell.h"

extern char **environ;

#ifndef UNIT_TESTS


int create_history(void)
{
    int fd;

    fd = open("/$HOME.minishell_history", O)
}




int main(int ac, char **av, char **env)
{
    char *line = "-> ";
    char *prompt;
    char **tokens;


    create_history();



    while((prompt = readline(line)))
    {
        add_history(prompt);
        execve("/bin/history", NULL, env);




        // tokens = tokenizer(prompt);
        // parser(tokens);


    }





    return (0);
}
#endif


// (cd /tmp && touch "file" && "echo'hello'" > file && grep 'hello' file | tee result.txt) || echo 'Error' > error.log
