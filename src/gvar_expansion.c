#include "minishell.h"

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

