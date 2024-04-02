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
        if (is_single_op(string, i) || is_double_op(string, i))
            count++;
        i++;
    }
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
    int     flag;
    int     i;
    int     j;

    flag = 0;
    i = 0;
    j = 0;
    res = malloc(sizeof(char *) * (count_op(string) + 1) * 2);
    // printf("count_op: %d\n", count_op(string) * 2);

    while (string[i])
    {
        if (is_double_op(string, i) && flag != 1)
        {
            flag = 1;
            res[j++] = ft_substr(string, i, 2);
            // printf("token D: %s\n", res[j - 1]);
            i += 2;
        }
        else if (is_single_op(string, i) && flag != 1)
        {
            flag = 1;
            res[j++] = ft_substr(string, i++, 1);
            // printf("token S: %s\n", res[j - 1]);
        }
        else
        {
            int start = i;
            while (string[i] && !is_double_op(string, i) && !is_single_op(string, i))
                i++;
            if (i > start)
            {
                res[j++] = ft_substr(string, start, i - start);
                // printf("token W: %s\n", res[j - 1]);
            }
            flag = 0;
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
		else if ((string[i] == c || i == ft_strlen(string)) && index >= 0 && is_in_quotes(string, i) == 0)
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

char    **tokenizer(char *string, int status)
{
    char    *normalized_input;
    char    **sp_tokenized;
    char    ***op_tokenized;
    char    *temp;
    int i;
    int j;

    quotes_error_check(string);

    normalized_input = input_normalizer(string);
    sp_tokenized = sp_tokenizer(normalized_input, ' ');
    free(normalized_input);
    i = 0;
    while (sp_tokenized[i])
        i++;
    op_tokenized = malloc((i + 1) * sizeof(char **));
    i = 0;
    while (sp_tokenized[i])
    {
        op_tokenized[i] = op_tokenizer(sp_tokenized[i]);
        free(sp_tokenized[i]);
        i++;
    }
    free(sp_tokenized);
    op_tokenized[i] = 0;

    char **tokenized;
    tokenized = flatten_3d_array(op_tokenized);

    expand_vars(tokenized, status);

    return (tokenized);
}


