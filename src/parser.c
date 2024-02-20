#include "minishell.h"

char    *input_normalizer(char *input)
{
    int     i;
    int     j;
    int     flag;
    char    *output;

    output = malloc(sizeof(char) * (ft_strlen(input) + 1));

    j = 0;
    i = 0;
    while (ft_isspace(input[i]) && input[i])
    {
        if (ft_isspace(input[i]) != ' ')
            input[i] = ' ';
        i++;
    }
    while (input[i])
    {
        if (ft_isspace(input[i]) && ft_isspace(input[i]) != ' ')
            input[i] = ' ';
        else if (ft_isspace(input[i]))
            if (flag && input[i + 1] != 0 && !ft_isspace(input[i + 1]))
                output[j++] = ' ';
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



// int	parser(char *input)
// {
//     int     token_start;
//     int     token_end;
//     int     i;

//     char    *token;

//     i = 0;
//     while (input[i])
//     {
//         while (ft_isspace(input[i]) == true)
//         {
//             i++;
//         }
//         if (is_out_of_quotes(input, i) == true)
//         {
//             if (is_char_special(input[i]) == true)
//             {
//                 if (input[i + 1] == input[i])
//                 {
//                     token_start = i;
//                     token_end = i + 1;
//                 }
//                 else
//                 {
//                     while ()
//                 }
//             }
//         }
//     }
//     return (0);
// }


int	is_char_special(char c)
{
    if (c == '|' || c == '&' || c == '<' || c == '>')
        return (c);

    if (c == '(' || c == ')' || c == '$'
            || c == '\'' || c == '\"')
        return (c);

    return (0);
}
