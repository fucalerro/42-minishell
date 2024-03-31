#include "minishell.h"

char    *expand_last_status(int status, char *token)
{
    char *status_string;

    status_string = ft_itoa(status);

    if (token[2])
        token = ft_strjoin(status_string, &token[2]);
    else
        token = ft_strdup(status_string);
    free(status_string);
    return (token);
}

void    expand_vars(char **tokens, int status)
{
    int i;
    char *tmp;

    i = 0;
    while (tokens[i])
    {
        if (tokens[i][0] == '$')
        {
            if (tokens[i][1] == '?')
            {
                tmp = ft_strdup(tokens[i]);
                tokens[i] = expand_last_status(status, tmp);
                free(tmp);
            }
            else
                tokens[i] = ft_strdup(var_expander(tokens[i]));
        }
        i++;
    }
}

/**
 * @brief expand a variable in a string
 *
 * @param string string to expand
 * @return char* pointer to expanded string
 */
char    *var_expander(char *string)
{
    char    *var_value;

    if (*(string++) == '$')
        var_value = getenv(string);
    return (var_value);
}

