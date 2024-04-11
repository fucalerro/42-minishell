#include "minishell.h"

int is_single_op(char *string, int i)
{
    char    *single_op = "&|<>()";

    if (string[i] && ft_strchr(single_op, string[i]))
        return (true);
    return (false);
}

int is_double_op(char *string, int i)
{
    char    *double_op[] = { "<<", ">>" };
    int     op_index;

    if (string[i] == 0 || string[i + 1] == 0)
        return false;

    op_index = 0;
    while (op_index < sizeof(double_op) / sizeof(double_op[0]))
    {
        if (ft_strncmp(&string[i], double_op[op_index], 2) == 0)
            return (true);
        op_index++;
    }
    return (false);
}

int count_op(char *string)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (string[i])
    {
        if ((is_single_op(string, i) || is_double_op(string, i)) && !is_in_quotes(string, i))
            count++;
        i++;
    }
    // printf("count: %d\n", count);
    return (count);
}


/**
 * @brief convert a string into a table of Operator and Word tokens
 * @param string input string
 * @return char** table of tokens
 */
char    **op_tokenizer(char *string)
{
    char    **res;
    int     op_flag;
    int     i;
    int     j;
    // int     quote_type;

    op_flag = 0;
    i = 0;
    j = 0;
    res = malloc(sizeof(char *) * (count_op(string) + 1) * 2);


    while (string[i])
    {
        if (is_double_op(string, i) && !op_flag && !is_in_quotes(string, i))
        {
            op_flag = true;
            res[j++] = ft_substr(string, i, 2);
            i += 2;
        }
        else if (is_single_op(string, i) && !op_flag && !is_in_quotes(string, i))
        {
            op_flag = true;
            res[j++] = ft_substr(string, i++, 1);
        }
        else
        {
            int start = i;
            while (string[i] && ((!is_double_op(string, i) && !is_single_op(string, i)) || is_in_quotes(string, i)))
                i++;
            if (i > start)
            {
                res[j++] = ft_substr(string, start, i - start);
            }
            op_flag = false;
        }
    }
    res[j] = 0;
    return (res);
}

/**
 * @brief convert a string into a table of tokens based on Space delimiter
 *
 * @param string
 * @param c
 * @return char**
 */
char	**sp_tokenizer(char *string, char c)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**res;

	i = -1;
	j = 0;
	index = -1;
	res = malloc((wordcounter(string, c) + 1) * sizeof(char *));
	if (res == 0)
		return (0);
	while (++i <= ft_strlen(string))
	{
		if (string[i] != c && index < 0)
			index = i;
		else if ((string[i] == c || i == ft_strlen(string)) && index >= 0 && !is_in_quotes(string, i))
		{
			res[j++] = wordmaker(string, index, i);
			index = -1;
		}
	}
	res[j] = 0;
	return (res);
}

int quotes_error_check(char *string)
{
    int len;
    int err;

    // check if quotes are closed
    len = ft_strlen(string);
    if (is_in_quotes(string, len - 1) == 1)
    {
        printf("Quotes are not closed\n");
        exit(1);
    }
	return (0); //random value to silence the warning
}


char    *set_is_in_quotes(char *token)
{
    char *res;
    int i;

    res = malloc(sizeof(char) * (ft_strlen(token) + 1));
    i = 0;
    while (token[i])
    {
        if (is_in_quotes(token, i) == SINGLE_QUOTE)
            res[i] = 'S';
        else if (is_in_quotes(token, i) == DOUBLE_QUOTE)
            res[i] = 'D';
        else
            res[i] = 'N';
        i++;
    }
    return (res);
}


t_tokens    **quotes_tokenizer(char **tokens)
{
    int i;
    t_tokens **res;

    res = malloc(sizeof(t_tokens *) * (get_elem_count_arr(tokens) + 1));

    i = 0;
    while (tokens[i])
    {
        res[i] = malloc(sizeof(t_tokens));
        // if (ft_strchr(tokens[i], '\'') || ft_strchr(tokens[i], '\"'))
        // {
            res[i]->quoted = is_quote(tokens[i][0]);
            char *temp = all_quotes_remover(tokens[i]);
            // free(tokens[i]);
            res[i]->token = ft_strdup(temp);
        // }
        // else
            // res[i]->token = ft_strdup(tokens[i]);
        i++;
    }
    res[i] = 0;
    return (res);
}



t_tokens **tokenizer(char *string, int status)
{
    char    *normalized_input;
    char    **sp_tokenized;
    char    ***op_tokenized;
    char    *temp;
    int i;
    int j;

    t_tokens **tokens;

    quotes_error_check(string);

    normalized_input = input_normalizer(string);
    sp_tokenized = sp_tokenizer(normalized_input, ' ');
    // free(normalized_input);
    i = 0;
    while (sp_tokenized[i])
        i++;
    op_tokenized = malloc((i + 1) * sizeof(char **));
    i = 0;


    // PL;
    expand_env_vars(sp_tokenized, status);
    // print_string_tab(sp_tokenized);

    while (sp_tokenized[i])
    {
        op_tokenized[i] = op_tokenizer(sp_tokenized[i]);
        // free(sp_tokenized[i]);
        i++;
    }
    // free(sp_tokenized);
    op_tokenized[i] = 0;


    char **tokenized;
    tokenized = flatten_3d_array(op_tokenized);


    tokens = quotes_tokenizer(tokenized);

    // print_tokens(tokens);

    // printf("------------\n");
    // print_string_tab(tokenized);
    // printf("------------\n");

    return (tokens);
}


