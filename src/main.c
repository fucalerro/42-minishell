#include "minishell.h"

int main(int ac, char **av, char **env)
{
    char *user_input; // = "      (cd /tmp && touch file && echo \"hello\" > file && grep \"hello\" file | tee result.txt) || echo \"Error\" > error.log          ";

    user_input = readline("minishell: ");


    for (int i = 0; i < ft_strlen(user_input) - 1; i++)
    {
        printf("char: %c    |   in quote: %d\n", user_input[i], is_in_single_quotes(user_input, i));

    }
    // parser(user_input);

    return (0);
}



// (cd /tmp && touch "file" && "echo'hello'" > file && grep 'hello' file | tee result.txt) || echo 'Error' > error.log          
