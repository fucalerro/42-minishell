#include "minishell.h"

int is_in_double_quotes(char *input, int index)
{
    int is_in_qote;
    int flag;
    int i;

    flag = 0;
    i = -1;
    is_in_qote = false;
    if (is_in_single_quotes(input, i) == true)
        return (false);
    while (input[++i])
    {
        flag = 0;
        if (input[i] == '\"' && is_in_qote == false)
        {
            is_in_qote = true;
            flag = 1;
        }
        if (input[i] == '\"' && is_in_qote == true && flag == 0)
            is_in_qote = false;
        if (i == index)
            return (is_in_qote);
    }
    return (-1);
}

int is_in_single_quotes(char *input, int index)
{
    int is_in_qote;
    int flag;
    int i;

    flag = 0;
    i = -1;
    is_in_qote = false;
    if (is_in_double_quotes(input, i) == true)
        return (false);
    while (input[++i])
    {
        flag = 0;
        if (input[i] == '\'' && is_in_qote == false)
        {
            is_in_qote = true;
            flag = 1;
        }
        if (input[i] == '\'' && is_in_qote == true && flag == 0)
            is_in_qote = false;
        if (i == index)
            return (is_in_qote);
    }
    return (-1);
}

int is_in_quotes(char *input, int index)
{
    if (is_in_single_quotes(input, index) == true)
        return (SINGLE_QUOTE);
    if (is_in_double_quotes(input, index) == true)
        return (DOUBLE_QUOTE);
    else
        return (0);
}

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
        if (ft_isspace(input[i]) != ' ')
            input[i] = ' ';
        i++;
    }
    while (input[i])
    {
        while (is_in_quotes(input, i) > 0)
            i++;
        if (ft_isspace(input[i]) && ft_isspace(input[i]) != ' ')
            input[i] = ' ';
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

void split_quotes(char *s)
{
    int quote_start;
    int quote_end;
    int i;
    int j;
    char *token;

    i = 0;
    j = 0;
    quote_end = -1;
    quote_start = -1;

    while (s[i])
    {
        if (is_quote(s[i]) && quote_start < 0)
        {
            quote_start = i;
            quote_end = i;
        }
        if (is_quote(s[i]) && quote_start > 0)
        {
            quote_end = i;
            quote_start = -1;
        }
        i++;
    }

    token = malloc(((quote_end - quote_start) + 1) * sizeof(char));

    // printf("start: %d\n", quote_start);
    // printf("end: %d\n", quote_end);

    while (quote_start < quote_end)
    {
        token[j++] = s[quote_start++];
    }

    printf("%s\n", token);
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

    split_quotes(input_normalized);

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
