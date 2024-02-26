#include "minishell.h"

#ifndef UNIT_TESTS
int main(int ac, char **av, char **env)
{
    char *user_input = "\"\"\"\"";

    // user_input = readline("minishell: ");
    // printf("%d\n", is_in_quotes(user_input, 400));

    // printf("%s\n", input_normalizer(user_input));
    printf("%d\n", quotes_counter(user_input));

    // parser(user_input);


    return (0);
}
#endif


// (cd /tmp && touch "file" && "echo'hello'" > file && grep 'hello' file | tee result.txt) || echo 'Error' > error.log
