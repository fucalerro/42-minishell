#include "minishell.h"

char *get_var_name(char *token)
{
    char *var_name;
    int i;
    int j;

    i = 1;
    j = 0;
    if (token[i] == '?')
    {
        return (ft_strdup("?"));
    }
    if (!token[i] || (!ft_isalnum(token[i]) && token[i] != '_'))
    {
        return (ft_strdup("$"));
    }
    var_name = malloc(sizeof(char) * ft_strlen(token) + 1);
    while (token[i] && (ft_isalnum(token[i]) || token[i] == '_'))
    {
        var_name[j++] = token[i++];
    }
    var_name[j] = 0;
    return (var_name);
}

char    *get_var_value(char *var_name, int status)
{
    char *var_value;

    if (!ft_strcmp(var_name, "$"))
    {
        return (ft_strdup("$"));
    }

    if (!ft_strcmp("?", var_name))
        return (ft_itoa(status));

    var_value = getenv(var_name);
    if (var_value)
        return (ft_strdup(var_value));
    return (0);
}

int get_nbr_of_vars(char *token)
{
    int i;
    int nbr_of_vars;

    i = 0;
    nbr_of_vars = 0;
    while (token[i])
    {
        if (token[i] == '$' && is_in_quotes(token, i) != SINGLE_QUOTE)
            nbr_of_vars++;
        i++;
    }
    return (nbr_of_vars);
}

char *expand_token(char *token, int status)
{
    char *var_value;
    char *var_name;
    int nbr_of_vars;
    int i;
    int j;
    int k;
    char **res;

    nbr_of_vars = get_nbr_of_vars(token);
    res = malloc(sizeof(char *) * (nbr_of_vars * 3 + 1));

    j = 0;
    i = 0;
    while (token[i])
    {
        if (is_in_quotes(token, i) == SINGLE_QUOTE)
        {
            k = i;
            while (token[k] && token[k] != '\'')
                k++;
            res[j++] = ft_substr(token, i - 1, (k - i) + 2);
            i = k + 1;
        }
        else if (token[i] == '$' && is_in_quotes(token, i) != SINGLE_QUOTE)
        {
            var_name = get_var_name(&token[i]);
            var_value = get_var_value(var_name, status);
            if (var_value)
            {
                if (!ft_strcmp(var_value, "$"))
                    i--;
                res[j++] = ft_strdup(var_value);
            }
            else
                res[j++] = ft_strdup("");
            i += ft_strlen(var_name) + 1;
        }
        else
        {
            k = i;
            while (token[k] && token[k] != '$')
                k++;
            res[j++] = ft_substr(token, i, k - i);
            i = k;
        }
    }
    res[j] = 0;
    char *new_token = flatten_2d_array(res);
    return (new_token);
}

void    expand_env_vars(char **tokens, int status)
{
    int i;
    char *tmp;

    i = 0;
    while (tokens[i])
    {
        if (ft_strchr(tokens[i], '$'))
        {
            tmp = expand_token(tokens[i], status);
            // PL;
            if (tmp)
            {
                tokens[i] = ft_strdup(tmp);
                free(tmp);
            }
        }
        i++;
    }
}
