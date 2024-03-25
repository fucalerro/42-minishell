#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>


extern char **environ;

#ifndef UNIT_TESTS
int main(int ac, char **av, char **env)
{
	char *line = "minishel: ";
	char *promt;
	while((promt = readline(line)))
	{
		printf("I got : %s\n", promt);
	}
    return (0);
}
#endif


// (cd /tmp && touch "file" && "echo'hello'" > file && grep 'hello' file | tee result.txt) || echo 'Error' > error.log
