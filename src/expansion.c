#include "minishell.h"

char    *expand_last_status(int status, char *token)
{
    char *status_string;

    status_string = ft_itoa(status);

    if (token[2])
        token = ft_strjoin(status_string, &token[2]);
    else
        token = ft_strdup(status_string);
    // free(status_string);
    return (token);
}

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
    if (!token[i] || !ft_isalnum(token[i]))
    {
        return (0);
    }
    var_name = malloc(sizeof(char) * ft_strlen(token) + 1);
    while (token[i] && ft_isalnum(token[i]))
    {
        var_name[j++] = token[i++];
    }
    var_name[j] = 0;
    return (var_name);
}

char    *get_var_value(char *var_name, int status)
{
    char *var_value;

    if (!ft_strcmp("?", var_name))
        return (ft_itoa(status));

    var_value = getenv(var_name);
    if (var_value)
        return (ft_strdup(var_value));
    return (0);
}

char *expand_token(char *token, int status)
{
    char *var_value;
    char *var_name;
    char *new_token;
    int new_token_len;

    char **res;


    int nbr_of_vars;
    int i;

    i = 0;
    nbr_of_vars = 0;

    while (token[i])
    {
        if (token[i] == '$' && is_in_quotes(token, i) != SINGLE_QUOTE)
            nbr_of_vars++;
        i++;
    }
    printf("nbr_of_vars: %d\n", nbr_of_vars);
    res = malloc(sizeof(char *) * (nbr_of_vars * 3 + 1));


    int j;
    i = 0;
    j = 0;
    new_token_len = 0;

    while (token[i])
    {
        printf("token[i]: %c\n", token[i]);
        if (token[i] == '$' && is_in_quotes(token, i) != SINGLE_QUOTE)
        {
            var_name = get_var_name(&token[i]);
            var_value = get_var_value(var_name, status);
            if (var_value)
            {
                res[j++] = ft_strdup(var_value);
                printf("res[j]: %s\n", res[j - 1]);
            }
        }
        else
        {


            res[j++] = ft_strdup(&token[i]);
            printf("res[j]: %s\n", res[j - 1]);
            // new_token[new_token_len++] = token[i++];
            // new_token[new_token_len] = 0;
        }
        i++;
    }
    res[j] = 0;

    printf("------------\n");

    print_string_tab(res);


    // free(var_name);
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
            if (tmp)
            {
                tokens[i] = ft_strdup(tmp);
                // free(tmp);
            }
        }
        i++;
    }
}
