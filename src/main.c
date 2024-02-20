#include "minishell.h"

int main(int ac, char **av, char **env)
{
    char *user_input = "      (cd       /tmp           && touch         file && echo   \"hello\" > file && grep \"hello\" file | tee result.txt) || echo \"Error\" > error.log          ";

    // count_char(user_input, "(");
    // count_char(user_input, ")");
    // is_char_count_even(user_input, "\'");
    // is_char_count_even(user_input, "\"");


    char *output = input_normalizer(user_input);
    printf("%s\n", output);

    return (0);
}
