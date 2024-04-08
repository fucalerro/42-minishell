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

char *expand_var(char *token, int status)
{
    char *var_value;
    char *var_name;
    char *new_token;
    int new_token_len;

    var_name = malloc(sizeof(char) * ft_strlen(token) + 1);
    new_token = malloc(sizeof(char) * ft_strlen(token) + 1);

    int i;
    int j;
    i = 0;
    j = 0;
    new_token_len = 0;
    while (token[i])
    {
        if (token[i] == '$' && is_in_quotes(token, i) != 1)
        {
            if (token[i + 1] == '?')
            {
                char *temp = ft_strjoin(new_token, ft_itoa(status));
                free(new_token);
                new_token = temp;
                new_token_len = ft_strlen(new_token);
                i += 2;
            }
            else if (!token[i + 1] || !ft_isalnum(token[i + 1]))
            {
                new_token[new_token_len++] = token[i++];
                new_token[new_token_len] = 0;
            }
            else
            {
                i++;
                j = 0;
                while (token[i] && ft_isalnum(token[i]))
                {
                    var_name[j++] = token[i++];
                }
                var_name[j] = 0;
                var_value = getenv(var_name);
                if (var_value)
                {
                    char *temp = ft_strjoin(new_token, var_value);
                    free(new_token);
                    new_token = temp;
                }
                new_token_len = ft_strlen(new_token);
            }
        }
        else
        {
            new_token[new_token_len++] = token[i++];
            new_token[new_token_len] = 0;
        }
    }
    free(var_name);
    return (new_token);
}

void    expand_env_vars(char **tokens, int status)
{
    int i;
    char *tmp;

    i = 0;
    while (tokens[i])
    {
        char *tmp;

        tmp = expand_var(tokens[i], status);
        if (tmp)
        {
            tokens[i] = ft_strdup(tmp);
            free(tmp);
        }
        // if (tokens[i][0] == '$')
        // {
        //     if (tokens[i][1] == '?')
        //     {
        //         tmp = ft_strdup(tokens[i]);
        //         tokens[i] = expand_last_status(status, tmp);
        //         free(tmp);
        //     }
        //     else
        //         tokens[i] = ft_strdup(var_expander(tokens[i]));
        // }
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

