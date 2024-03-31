#include "minishell.h"

void    expand_vars(char **tokens)
{
    int i;
    i = 0;
    while (tokens[i])
    {
        if (tokens[i][0] == '$')
            tokens[i] = ft_strdup(var_expander(tokens[i]));
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

