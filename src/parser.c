#include "minishell.h"

int is_metachar(char c)
{
    if (c == '|' || c == '<' || c == '>')
        return (1);
    return (0);
}

/**
 * @brief check if a character in a string is within single or double quotes.
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
    while (input[++i] && i <= index)
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
        while (is_in_quotes(input, i) > 0 && input[i])
        {
            output[j++] = input[i++];
        }
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

/**
 * @brief Count the number of words in a string. Words are separated by spaces.
 * Words within single or double quotes are considered as one word.
 *
 * @param input
 * @return int
 */
int word_counter_quotes(char *input)
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


int is_quote(char c)
{
    if (c == '\'')
        return (SINGLE_QUOTE);
    if (c == '\"')
        return (DOUBLE_QUOTE);
    else
        return (0);
}

char    *quotes_remover(char *string)
{
    char *res;

    if (!is_quote(string[0]))
        return (ft_strdup(string));
    res = malloc(sizeof(char) * (ft_strlen(string) + 1));
    int i = 0;
    while (string[i])
    {
        res[i] = string[i + 1];
        i++;
    }
    res[i - 2] = 0;
    return (res);
}


char **consolidate_cmd(char **input, int i, int *arg_count)
{
    char **cmd;
    int j;
    int cmd_len;

    j = i;
    cmd_len = 0;
    while (input[j] && is_metachar(input[j][0]) == 0)
    {
        cmd_len++;
        j++;
    }
    cmd = malloc(sizeof(char *) * (cmd_len + 1));
    j = 0;
    while (input[i] && is_metachar(input[i][0]) == 0)
    {
        if (is_quote(input[i][0]))
        {
            char *tmp = quotes_remover(input[i]);
            cmd[j] = ft_strdup(tmp);
            free(tmp);
        }
        else
            cmd[j] = ft_strdup(input[i]);
        i++;
        j++;
    }
    *arg_count = cmd_len - 1;
    cmd[j] = 0;
    return (cmd);
}


t_node *parser(char **input)
{
    t_node *lst;
    int i;
    int token_count;
    char **consolidated_cmd;
    int arg_count;

    lst = NULL;
    token_count = get_elem_count(input);
    i = 0;
    while (input[i])
    {
        if (ft_strncmp(input[i], "|", 1) == 0)
        {
            lst_append(&lst, T_PIPE, NULL, NULL, NULL);
        }
        else if (ft_strcmp(input[i], ">") == 0 && i + 1 < token_count)
        {
            lst_append(&lst, T_OUTFILE, input[i + 1], NULL, NULL);
            i ++;
        }
        else if (ft_strcmp(input[i], "<") == 0 && i + 1 < token_count)
        {
            lst_append(&lst, T_INFILE, input[i + 1], NULL, NULL);
            i ++;
        }
        else if (ft_strcmp(input[i], ">>") == 0 && i + 1 < token_count) // append mode
        {
            lst_append(&lst, T_OUTFILE_APPEND, input[i + 1], NULL, NULL);
            i ++;
        }
        else if (ft_strcmp(input[i], "<<") == 0 && i + 1 < token_count) // heredoc
        {
            quotes_remover(input[i + 1]);
            lst_append(&lst, T_HEREDOC, NULL, NULL, input[i + 1]);
            i ++;
        }
        else
        {
            consolidated_cmd = consolidate_cmd(input, i, &arg_count);
            lst_append(&lst, T_CMD, NULL, consolidated_cmd, NULL);
            i += arg_count;
        }
        i++;
    }
    return (lst);
}

