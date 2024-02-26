#include "minishell.h"

#ifndef UNIT_TESTS
int main(int ac, char **av, char **env)
{
    char *user_input = "aa|bb||cc||dd";

    printf("%s\n\n", user_input);
    // user_input = readline("minishell: ");
    // printf("%d\n", is_in_quotes(user_input, 400));

    // printf("%s\n", input_normalizer(user_input));
    // printf("%d\n", word_counter_quotes(user_input));

    char *input = input_normalizer(user_input);

    // quotes_splitter(input);
    op_tokeniser(input);



    // parser(user_input);


    return (0);
}
#endif


// (cd /tmp && touch "file" && "echo'hello'" > file && grep 'hello' file | tee result.txt) || echo 'Error' > error.log
