#include "minishell.h"

/**
 * @brief check if a character in a string is within single or double quotes.
 * If the index > strlen, it checks the last character.
 *
 * @param input string
 * @param index character index to check
 * @return 1 if within quotes, 0 if not. Returns 1 even if the quote is not closed.
 */
int is_in_quotes(char *input, int index)
{
    int in_double_quote;
    int in_single_quote;
    int i;

    i = -1;
    in_double_quote = false;
    in_single_quote = false;
    while (input[++i])
    {
        if (input[i] == '\'' && !in_double_quote)
            in_single_quote = !in_single_quote;
        else if (input[i] == '\"' && !in_single_quote)
            in_double_quote = !in_double_quote;
        if (i == index)
            break;
    }
    // printf("in_quotes: %d\n", in_single_quote || in_double_quote);
    return (in_single_quote || in_double_quote);
}

/**
 * @brief Removes extra spaces and replaces all sort of tabs for spaces.
 * Do not change the portion that are in single or double quotes.
 *
 * @param input
 * @return char*
 */
char *input_normalizer(char *input)
{
    int i;
    int j;
    int flag;
    char *output;

    output = malloc(sizeof(char) * (ft_strlen(input) + 1));

    j = 0;
    i = 0;
    while (ft_isspace(input[i]) && input[i])
    {
        if (ft_isspace(input[i]) != 32)
            output[i] = ' ';
        i++;
    }
    while (input[i])
    {
        while (is_in_quotes(input, i) > 0)
            output[j++] = input[i++];
        if (ft_isspace(input[i]) && ft_isspace(input[i]) != ' ')
        {
            output[j++] = ' ';
        }
        else if (ft_isspace(input[i]))
        {
            if (flag && input[i + 1] != 0 && !ft_isspace(input[i + 1]))
                output[j++] = ' ';
        }
        else
        {
            output[j++] = input[i];
            flag = 1;
        }
        i++;
    }
    output[j] = 0;
    return (output);
}

// int get_quoted_string_len(char string, int start)
// {
//     int i;

//     int in_quote;
//     int prev_in_quote;

//     in_quote = false;
//     prev_in_quote = false;

//     i = 0;
//     while (in_quote = prev_in_quote)
// }

int quotes_counter(char *input)
{
    int i;
    int quote_count;

    int in_quote = false;
    int prev_in_quote = false;

    quote_count = 0;

    i = 0;
    if (input[i] == '\'' || input[i] == '\"')
        quote_count--;
    while (input[i])
    {
    in_quote = is_in_quotes(input, i);
        if (in_quote != prev_in_quote)
            quote_count++;
        prev_in_quote = in_quote;
    i++;
    }
    if (input[--i] == '\'' || input[i] == '\"')
        quote_count--;
    return (quote_count + 1);
}

char **quotes_splitter(char *input)
{
    char   **res;

    // res = malloc()


    // int     i;
    // int     in_quote;
    // int     prev_in_quote;
    // char    **res;
    // int     j;
    // int     len;

    // in_quote = false;
    // prev_in_quote = false;

    // j = 0;
    // i = 0;
    // while (input[i])
    // {
    //     in_quote = is_in_quotes(input, i);
    //     if (in_quote != prev_in_quote)
    //     {
    //         len = 0;
    //         while (is_in_quotes(input, i) == is_in_quotes(input, i))
    //         {

    //         }
    //         res[j] = ft_substr(input, i, )
    //     }


    //     prev_in_quote = in_quote;
    //     i++;
    // }




}



int is_quote(char c)
{
    if (c == '\'')
        return (SINGLE_QUOTE);
    if (c == '\"')
        return (DOUBLE_QUOTE);
    else
        return (0);
}

int parser(char *input)
{
    int token_start;
    int token_end;
    int i;
    int quoted_sg;
    int quoted_db;
    char *token;
    char *input_normalized;

    input_normalized = input_normalizer(input);

    printf("%s\n", input_normalized);

    // splitter(input_normalized);

    return (0);
}

int is_char_special(char c)
{
    if (c == '|' || c == '&' || c == '<' || c == '>')
        return (c);

    if (c == '(' || c == ')' || c == '$' || c == '\'' || c == '\"')
        return (c);

    return (0);
}
