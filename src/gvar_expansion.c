#include "minishell.h"

char    *var_expander(char *string)
{
    char    *var_value;

    if (*(string++) == '$')
        var_value = getenv(string);
    return (var_value);
}
